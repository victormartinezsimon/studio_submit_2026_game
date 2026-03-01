#pragma once
#include <utility>
#include "WorldObject.h"

class Bullet:public WorldObject
{
public:
	Bullet();

public:
	void SetVelocity(float vel);
	void Update(const float deltaTime);


private:
	float _velocityY;
};