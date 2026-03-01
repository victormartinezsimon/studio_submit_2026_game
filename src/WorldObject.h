#pragma once
#include <utility>

class WorldObject
{
public:
	std::pair<unsigned int, unsigned int> GetPosition() const
	{
		return { _X, _Y };
	}
	void SetPosition(unsigned int x, unsigned int y)
	{
		_X = x;
		_Y = y;
	}
	
public:
	unsigned int GetWidth() const
	{
		return _width;
	}
	unsigned int GetHeight() const
	{
		return _height;
	}
	void SetSize(unsigned int width, unsigned int height)
	{
		_width = width;
		_height = height;
	}

public:
public:
	bool GetTeam() const
	{
		return _playerTeam;
	}
	void SetTeam(bool playerTeam)
	{
		_playerTeam = playerTeam;
	}

protected:
	unsigned int _X = 0;
	unsigned int _Y = 0;
	unsigned int _width = 0;
	unsigned int _height = 0;

	bool _playerTeam;
};