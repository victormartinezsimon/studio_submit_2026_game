#include "LinuxPainter.h"
#include "Plane.h"
#include "Bullet.h"

LinuxPainter::LinuxPainter()
{
}

LinuxPainter::~LinuxPainter()
{
}

void LinuxPainter::PaintBackground()
{
}

void LinuxPainter::BeginPaint()
{
}

void LinuxPainter::EndPaint()
{
}

float LinuxPainter::GetDeltaTime()
{
	return 0.16;
}

bool LinuxPainter::HasEnded()
{
	return false;
}

void LinuxPainter::PaintPlayer(Plane* player)
{
}
void LinuxPainter::PaintEnemy(Plane* enemy)
{
}

void LinuxPainter::PaintBullet(Bullet* bullet)
{
	int x = bullet->GetX() - bullet->GetWidth() / 2;
	int y = bullet->GetY() - bullet->GetHeight() / 2;

}