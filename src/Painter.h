#pragma once
#include <array>
#include "GameConfig.h"

class Bullet;
class Plane;

class Painter
{
public:
	Painter() {}
	virtual ~Painter() {}

public:
	virtual void BeginPaint() = 0;
	virtual void EndPaint() = 0;
	virtual float GetDeltaTime() = 0;

public:
	virtual void PaintBackground() = 0;
	virtual void PaintPlayer(Plane* player) = 0;
	virtual void PaintEnemy(Plane* enemy) = 0;
	virtual void PaintBullet(Bullet* bullet) = 0;

public:
	virtual bool HasEnded() = 0;
};