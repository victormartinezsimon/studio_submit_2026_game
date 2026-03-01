#include "Bullet.h"
#include <cmath>

Bullet::Bullet():_velocityY(0)
{}

void Bullet::SetVelocity(float vel)
{
	_velocityY = vel;
}

void Bullet::Update(const float deltaTime)
{
	float newY = std::floor(deltaTime * _velocityY);
	_Y += newY;
}