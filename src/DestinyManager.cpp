#include "DestinyManager.h"
DestinyManager::DestinyManager():_generator(std::random_device{}()), _lastPosition(0){}

void DestinyManager::Reset()
{
    _lastPosition = 0;
}
void DestinyManager::AddPosition(float x, float y)
{
    if (_lastPosition > _positions.size())
    {
        return;
    }

    _positions[_lastPosition].x = x;
    _positions[_lastPosition].y = y;

    ++_lastPosition;
    
}
void DestinyManager::GetRandomPosition(float &x, float &y)
{
    x = _positions[0].x;
    y = _positions[0].y;
    //TODO: review this
/*
    std::uniform_int_distribution<int> positionDist(0, _lastPosition-1);
	int posID = positionDist(_generator);

    x = _positions[posID].x;
    y = _positions[posID].y;
    */
}

int DestinyManager::GetTotalPositions() const
{
    return _lastPosition;
}

