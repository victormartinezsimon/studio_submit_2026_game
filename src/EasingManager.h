#pragma once
#include "GameConfig.h"
#include <array>
#include <functional>
#include "Pool.h"
#include "Ease.h"

class EasingManager
{

public:
	void Update(const float deltaTime);

	int AddEase(float duration, float startX, float startY, 
		float endX, float endY, Ease::EASE_TYPES);

	int AddEase(float duration, float startX, float startY, 
		float endX, float endY, Ease::EASE_TYPES type, std::function<void(bool)> endCallback,
		std::function<void(float currentX, float currentY)> tickCallback);

	void KillEase(int id);
	void KillAll();

private:
	Pool<Ease, MAX_EASING_VALUES> _poolEases;
};