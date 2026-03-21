#pragma once
#include "GameConfig.h"
#include <array>
#include <functional>
#include "PainterManager.h"
#include "EasingManager.h"

class Alpha
{

public:
	bool Update(const float deltaTime);
	void ConfigureAlpha(float duration, bool isUI, float x, float y,
                            float width, float height, 
							PainterManager::SPRITE_ID sprite);
	
	void AddCallback(std::function<void()> callback);
	void Paint(PainterManager* _painter);
	void EndAlpha();
	void SetPosition(float x, float y);

private:
int ConfigureInternalAlpha(float duration, bool isUI, float x, float y,
                            float width, float height, 
							PainterManager::SPRITE_ID sprite);

public:
	void SetID(int id)
	{
		_id = id;
	}
	int GetID() const
	{
		return _id;
	}

	void SetEaseID(int id)
	{
		_easeID = id;
	}
	int GetEaseID() const
	{
		return _easeID;
	}

private:
	float _acumTime;
	float _duration;
	PainterManager::SPRITE_ID _sprite;
	int _currentX;
	int _currentY;
	bool _isUI;
	int _width;
	int _height;
	int _easeID;
	std::function<void()> _endCallback = nullptr;
	int _id;
};