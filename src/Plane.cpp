#include "Plane.h"

void Plane::SetCallbackFire(std::function<void(int, const Plane&)> fun)
{
	_callbackFire = fun;
}
void Plane::SetFireRate(float fireRate)
{
	_fireRate = fireRate;
}
void Plane::IncreaseFireRate(float increase)
{
	_fireRate += increase;
}
void Plane::SetBulletsTotalSources(int bullets)
{
	_bulletsTotalSources = bullets;
}

void Plane::SetHasShield(bool value)
{
	_hasShield = value;
}
bool Plane::GetHasShield() const
{
	return _hasShield;
}

void Plane::SetBulletsPerShot(int bullets)
{
	_bulletsPerShot = bullets;
}
int Plane::GetBulletsPerShot() const
{
	return _bulletsPerShot;
}


void Plane::Update(const float deltaTime)
{
	_currentAcumTime += deltaTime;

	if(_timeInmortal > 0)
	{
		_timeInmortal-= deltaTime;
	}

	if (_currentAcumTime > _fireRate)
	{
		for (int i = 0; i < _bulletsTotalSources; ++i)
		{
			if(_callbackFire)
			{
				_callbackFire(i, *this);
			}
		}
		_currentAcumTime = 0;
	}
}

void Plane::Reset(float value)
{
	_currentAcumTime = -value;
}

void Plane::SetTimeInmortal(float value)
{
	_timeInmortal = value;
}
float Plane::GetTimeInmortal() const
{
	return _timeInmortal;
}

void Plane::SetRandomMovementID(int value)
{
	_randomMovementID = value;
}
int Plane::GetRandomMovementID() const
{
	return _randomMovementID;
}
