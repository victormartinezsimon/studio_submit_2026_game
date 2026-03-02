#include "RaylibPainter.h"
#include "Plane.h"
#include "Bullet.h"

RaylibPainter::RaylibPainter() : _window(SCREEN_WIDTH, SCREEN_HEIGHT, "SUMMIT_2026")
{
}

void RaylibPainter::Paint()
{
	_window.ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}

void RaylibPainter::BeginPaint()
{
	BeginDrawing();
}

void RaylibPainter::EndPaint()
{
	EndDrawing();
}

bool RaylibPainter::HasEnded()
{
	return _window.ShouldClose();
}