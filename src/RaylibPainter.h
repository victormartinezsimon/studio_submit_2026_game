#pragma once
#include <array>
#include "GameConfig.h"
#include "raylib-cpp.hpp"


class Bullet;
class Plane;

class RaylibPainter
{
public:
	RaylibPainter();

public:
	void BeginPaint();
	void Paint();
	void EndPaint();

public:
	bool HasEnded();

private:
	raylib::Window _window;
};