#pragma once
#include <array>
#include "GameConfig.h"
#include "Painter.h"


class Bullet;
class Plane;

class LinuxPainter : public Painter
{
public:
	LinuxPainter();
	~LinuxPainter();

public:
	void BeginPaint() override;
	void EndPaint() override;
	float GetDeltaTime() override;

public:
	void PaintBackground() override;
	void PaintPlayer(Plane* player) override;
	void PaintEnemy(Plane* enemy) override;
	void PaintBullet(Bullet* bullet) override;

private:

public:
	bool HasEnded() override;
};