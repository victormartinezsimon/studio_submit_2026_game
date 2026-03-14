#include "Painter.h"
#include <stdexcept>
#include <thread>

constexpr int ALPHA_INDEX = 8;

Painter::Painter()
{
	s_platform = SPInitPlatform();

	if (!s_platform)
	{
		throw std::runtime_error("failed creating platform");
	}

	stride = VPUGetStride(VIDEO_MODE, VIDEO_COLOR);
	frameBufferA.size = frameBufferB.size = stride * SCREEN_HEIGHT;
	SPAllocateBuffer(s_platform, &frameBufferA);
	SPAllocateBuffer(s_platform, &frameBufferB);

	VPUSetVideoMode(s_platform->vx, VIDEO_MODE, VIDEO_COLOR, EVS_Enable);
	init_palette(s_platform->vx);

	s_platform->sc->cycle = 0;
	s_platform->sc->framebufferA = &frameBufferA;
	s_platform->sc->framebufferB = &frameBufferB;

	VPUSetScanoutAddress(s_platform->vx, (uint32_t)frameBufferA.dmaAddress);
	VPUSetScanoutAddress2(s_platform->vx, (uint32_t)frameBufferB.dmaAddress);

	VPUSwapPages(s_platform->vx, s_platform->sc);
	VPUClear(s_platform->vx, 0x00000000);
	VPUSwapPages(s_platform->vx, s_platform->sc);
	VPUClear(s_platform->vx, 0x00000000);
}

Painter::~Painter()
{
}



void Painter::BeginPaint()
{
	VPUSwapPages(s_platform->vx, s_platform->sc);
}

void Painter::EndPaint()
{
	VPUSyncSwap(s_platform->vx, 0);
	VPUNoop(s_platform->vx);
	std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void Painter::PaintBackground()
{
	dst = (uint8_t *)s_platform->sc->writepage;
	fill_background(dst, stride, 0);
	//VPUClear(s_platform->vx,0xFF080F2A);//(8,15,42));
}

void Painter::fill_background(uint8_t *dst, uint32_t stride, uint32_t frame)
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		uint8_t *row = dst + (uint32_t)y * stride;
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			uint8_t v = (uint8_t)(16 + (((x + (int)(frame >> 1)) >> 4) & 7));
			row[x] = v;
		}
	}
}

void Painter::PaintItem(const uint8_t* sprite, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	masked_blit_8(dst, stride, SCREEN_WIDTH, SCREEN_HEIGHT, sprite, width, height, x, y, ALPHA_INDEX);
}

void Painter::init_palette(struct EVideoContext *vctx)
{
	VPUSetDefaultPalette(vctx);

	VPUSetPal(vctx, 0, 8,9,12);
	VPUSetPal(vctx, 1, 29,30,42);
	VPUSetPal(vctx, 2, 56,57,82);
	VPUSetPal(vctx, 3, 236,27,17);
	VPUSetPal(vctx, 4, 212,53,25);
	VPUSetPal(vctx, 5, 254,205,23);
	VPUSetPal(vctx, 6, 20,88,165);
	VPUSetPal(vctx, 7, 26,81,179);
	VPUSetPal(vctx, 8, 255,0,255);
	VPUSetPal(vctx, 9, 251,24,252);
	VPUSetPal(vctx, 10, 243,34,233);
	VPUSetPal(vctx, 11, 229,77,224);
	VPUSetPal(vctx, 12, 72,173,231);
	VPUSetPal(vctx, 13, 178,193,218);
	VPUSetPal(vctx, 14, 211,224,232);
	VPUSetPal(vctx, 15, 245,247,249);
}

void Painter::masked_blit_8(
	uint8_t *dst,
	uint32_t dst_stride,
	int dst_w,
	int dst_h,
	const uint8_t*src,
	int src_w,
	int src_h,
	int dst_x,
	int dst_y,
	uint8_t key)
#
{
	int src_x = 0;
	int src_y = 0;
	int w = src_w;
	int h = src_h;

	// Clip the source and destination rectangles to ensure we don't read/write out of screen bounds
	if (dst_x < 0)
	{
		src_x = -dst_x;
		dst_x = 0;
		w -= src_x;
	}
	if (dst_y < 0)
	{
		src_y = -dst_y;
		dst_y = 0;
		h -= src_y;
	}
	if (dst_x + w > dst_w)
		w = dst_w - dst_x;
	if (dst_y + h > dst_h)
		h = dst_h - dst_y;
	if (w <= 0 || h <= 0)
		return;

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	uint8x16_t keyv = vdupq_n_u8(key); // Broadcast the key to 16 bytes
#endif

	for (int y = 0; y < h; ++y)
	{
		uint8_t *d = dst + (uint32_t)(dst_y + y) * dst_stride + dst_x;
		const uint8_t *s = src + (src_y + y) * src_w + src_x;
		int x = 0;

		// If NEON is available, we can process 16 pixels at a time.
		// The key is compared against the source pixels, and if it matches,
		// the destination pixel is kept; otherwise, the source pixel is copied to the destination.
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
		for (; x + 15 < w; x += 16)
		{
			uint8x16_t sv = vld1q_u8(s + x);		 // Load source pixels
			uint8x16_t dv = vld1q_u8(d + x);		 // Load destination pixels
			uint8x16_t mask = vceqq_u8(sv, keyv);	 // Compare source pixels with key, result is 0xFF where equal, 0x00 where not
			uint8x16_t out = vbslq_u8(mask, dv, sv); // If mask bit is 1, select from dv (keep dest), else select from sv (copy src)
			vst1q_u8(d + x, out);					 // Store result back to destination
		}
#endif
		// Process any remaining pixels that don't fit into a 16-byte block
		for (; x < w; ++x)
		{
			uint8_t px = s[x];
			if (px != key)
				d[x] = px;
		}
	}
}
