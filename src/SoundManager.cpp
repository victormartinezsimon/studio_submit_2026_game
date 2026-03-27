#include "SoundManager.h"
#include "background_sound.h"

SoundManager::SoundManager(struct SPPlatform* platform)
	: m_platform(platform)
	, m_ctx(nullptr)
	, m_apuBuffer{}
	, m_moduleLoaded(false)
	, m_ready(false)
	, m_lastFrame(0)
{
	// Double buffer: two halves of SM_BUFFER_BYTE_COUNT each
	m_apuBuffer.size = SM_BUFFER_BYTE_COUNT * 2;
	SPAllocateBuffer(m_platform, &m_apuBuffer);
	memset(m_apuBuffer.cpuAddress, 0, SM_BUFFER_BYTE_COUNT * 2);
}

SoundManager::~SoundManager()
{
	Shutdown();
}

void SoundManager::Shutdown()
{
	if (m_ready)
	{
		xmp_end_player(m_ctx);
		m_ready = false;
	}
	if (m_moduleLoaded)
	{
		xmp_release_module(m_ctx);
		m_moduleLoaded = false;
	}
	if (m_ctx)
	{
		xmp_free_context(m_ctx);
		m_ctx = nullptr;
	}
}

void SoundManager::Prepare()
{
	m_ready = false;

	m_ctx = xmp_create_context();

	if (xmp_load_module_from_memory(m_ctx, space_alliance_mod, space_alliance_mod_len) < 0)
	{
		xmp_free_context(m_ctx);
		m_ctx = nullptr;
		return;
	}

	m_moduleLoaded = true;

	APUSetBufferSize(m_platform->ac, ABS_4096Bytes);
	APUSetSampleRate(m_platform->ac, ASR_22_050_Hz);

	if (xmp_start_player(m_ctx, 22050, 0) == 0)
	{
		// Pre-fill both buffer halves
		xmp_play_buffer(m_ctx, m_apuBuffer.cpuAddress, SM_BUFFER_BYTE_COUNT, 0);
		xmp_play_buffer(m_ctx, m_apuBuffer.cpuAddress + SM_BUFFER_BYTE_COUNT, SM_BUFFER_BYTE_COUNT, 0);

		APUStartDMA(m_platform->ac, (uint32_t)m_apuBuffer.dmaAddress);
		m_lastFrame = APUFrame(m_platform->ac);
		m_ready = true;
	}
}

void SoundManager::Update()
{
	if (!m_ready) { return; }

	uint32_t frame = APUFrame(m_platform->ac);
	if (frame == m_lastFrame) { return; }

	// Fill the inactive half while the hardware plays the other
	uint8_t* dst = m_apuBuffer.cpuAddress + (frame ? 0 : SM_BUFFER_BYTE_COUNT);
	if (xmp_play_buffer(m_ctx, dst, SM_BUFFER_BYTE_COUNT, 0) != 0)
	{
		m_ready = false;
		return;
	}

	APUStartDMA(m_platform->ac, (uint32_t)m_apuBuffer.dmaAddress);
	m_lastFrame = frame;
}