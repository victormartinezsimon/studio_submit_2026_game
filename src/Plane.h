#pragma once
#include <functional>
#include "WorldObject.h"

class Plane : public WorldObject
{
public:
	void Update(const float deltaTime);
	void Reset(float value);

public:
	void SetCallbackFire(std::function<void(int, const Plane&)> fun);

public:
	void SetFireRate(float fireRate);
	void IncreaseFireRate(float increase);

public:
	void SetBulletsTotalSources(int bullets);

public:
	void SetBulletsPerShot(int bullets);
	int GetBulletsPerShot() const;

public:
	void SetHasShield(bool value);
	bool GetHasShield() const;

public:
	void SetTimeInmortal(float value);
	float GetTimeInmortal() const;

public:
	void SetRandomMovementID(int value);
	int GetRandomMovementID() const;

private:
	std::function<void(int, const Plane&)> _callbackFire = nullptr;
	float _fireRate = 0;
	int _bulletsTotalSources = 1;
	float _currentAcumTime = 0;
	bool _hasShield = false;
	int _bulletsPerShot = 1;
	float _timeInmortal = 0;
	int _randomMovementID = -1;
};
