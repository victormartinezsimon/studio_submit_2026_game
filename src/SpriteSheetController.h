#pragma once
#include <functional>
#include "PainterManager.h"

class SpriteSheetController 
{
	public:
		SpriteSheetController();

	public:
		bool Update(const float deltaTime);
		void Paint(PainterManager* painter, float x, float y)const;
		void Paint(PainterManager* painter, float x, float y, float alpha)const;
		void PaintFrame(PainterManager* painter, float x, float y, int frameId)const;
		void PaintFrame(PainterManager* painter, float x, float y, int frameId, float alpha)const;
		void GetCoordsForFrame(int frameId, int& coordX, int& coordY)const;
		void Reset();

		void Configure(	const PainterManager* painter, PainterManager::SPRITE_ID sprite, unsigned int cols, unsigned int rows, float frameDuration);
		void Configure(	const PainterManager* painter, PainterManager::SPRITE_ID sprite, unsigned int cols, unsigned int rows, float frameDuration, bool loop);
		void Configure(	const PainterManager* painter, PainterManager::SPRITE_ID sprite);
		void Configure( const PainterManager* painter, const SpriteSheetController* other);
		void SetSprite(PainterManager::SPRITE_ID sprite, float width, float height);
		PainterManager::SPRITE_ID GetSprite()const;

		void GetSize(unsigned int& w, unsigned int& h)const;
		unsigned int GetWidth()const;
		unsigned int GetHeight()const;

		void SetFixedFrame(int value);

	private:
		unsigned int _cols;
		unsigned int _rows;
		float _frameDuration;
		PainterManager::SPRITE_ID _sprite;
		float _timeAcum;
		int _totalFrames;
		float _totalDuration;
		unsigned int _spriteWidth;
		unsigned int _spriteHeight;
		unsigned int _frameWidth;
		unsigned int _frameHeight;
		int _fixedFrame = -1;
		bool _loop;
};
