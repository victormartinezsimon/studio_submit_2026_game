#pragma once
#include <utility>

class Bullet
{
public:
	Bullet();

public:
	std::pair<unsigned int, unsigned int> GetPosition() const;
	void SetPosition(unsigned int x, unsigned int Y);
	
public:
	bool GetTeam() const;
	void SetTeam(bool playerTeam);

public:
	void SetVelocity(float vel);
	void Update(const float deltaTime);


private:
	unsigned int _X;
	unsigned int _Y;
	float _velocityY;
	bool _playerTeam;
};