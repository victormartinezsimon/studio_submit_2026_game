#pragma once
#include "GameConfig.h"
#include <array>
#include "Pool.h"
#include "PainterManager.h"
#include "SpriteSheetController.h"

class TrailManager
{

private:
	struct Trail
	{
		float x;
		float y;
		int width;
		int height;
		//PainterManager::SPRITE_ID sprite;
		//PainterManager::SPRITE_ID small_sprite;
		float currentLive;
		float maxLive;
		int _id;
		SpriteSheetController spriteSheetNormal;
		SpriteSheetController spriteSheetSmall;

		public:
			void SetID(int id)
			{
				_id = id;
			}
			int GetID() const
			{
				return _id;
			}
	};

public:
	void Update(const float deltaTime);
	int AddTrail(PainterManager* painter, float x, float y, int width, int height, float duration, PainterManager::SPRITE_ID sprite);
	int AddTrail(PainterManager* painter, float x, float y, int width, int height, float duration, PainterManager::SPRITE_ID sprite,
	PainterManager::SPRITE_ID small_sprite);
	void Paint(PainterManager* painter);

	SpriteSheetController* GetSpriteSheetNormal(int id);
	SpriteSheetController* GetSpriteSheetSmall(int id);

private:
	void Configure(PainterManager* painter, Trail& trail, float x, float y, int width, int height, float duration, PainterManager::SPRITE_ID sprite,
	PainterManager::SPRITE_ID small_sprite);
	void UpdateTrail(Trail& trail, const float deltaTime);
	void PaintTrail(PainterManager* painter, Trail& trail);
	
private:
	Pool<Trail, MAX_TRAILS> _poolTrail;
};