#pragma once
#include "GameConfig.h"
#include <array>
#include "PainterManager.h"
#include "EasingManager.h"

class AlphaManager
{

private:
	struct AlphaData
	{
		float acumTime;
		bool goDown;
		float duration;
		PainterManager::SPRITE_ID sprite;
		int currentX;
		int currentY;
		bool isUI;
		int width;
		int height;
		int easeID;
	};

public:
	AlphaManager(PainterManager* painterManager, EasingManager* easingManager);


public:
	void Update(const float deltaTime);
	bool AddUIAlpha(float duration, float x, float y, bool goDown, PainterManager::SPRITE_ID sprite);
	bool AddAlpha(float duration, float x, float y, bool goDown, float width, float height, PainterManager::SPRITE_ID sprite);
	bool AddUIAlpha(float duration, float x, float y, float endX, float endY, bool goDown, PainterManager::SPRITE_ID sprite);
	bool AddAlpha(float duration, float x, float y,  float endX, float endY, bool goDown, float width, float height, PainterManager::SPRITE_ID sprite);
	void FinishAll();
	void FinishAlpha(int id);
	void Paint();

private:
bool AddInternalAlpha(float duration, bool isUI, float startX, float startY,
                            float endX, float endY, bool goDown, float width, float height, PainterManager::SPRITE_ID sprite);

private:
	std::array<AlphaData, MAX_ALPHA_VALUES> _alphas;
	std::array<bool, MAX_ALPHA_VALUES> _inUse;
	PainterManager* _painterManager;
	EasingManager* _easingManager;
};