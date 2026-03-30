#include "Alpha.h"

bool Alpha::Update(const float deltaTime)
{
    _acumTime += deltaTime;

    float percent = _acumTime / _duration;
    if(percent >= 1.0)
    {
        EndAlpha();
        return true;
    }
    return false;
}

void Alpha::ConfigureAlpha(float duration, float x, float y,
                           PainterManager::SPRITE_ID sprite, float width, float height)
{
    _acumTime = 0;
    _duration = duration;
    _sprite = sprite;
    _currentX = x;
    _currentY = y;
    _width = width;
    _height = height;
    _endCallback = nullptr;
}

void Alpha::SetPosition(float x, float y)
{
    _currentX = x;
    _currentY = y;
}


void Alpha::AddCallback(std::function<void()> callback)
{
    _endCallback= callback;
}   


void Alpha::EndAlpha()
{
    if(_endCallback)
    {
        _endCallback();
    }

    _endCallback = nullptr;
}


void Alpha::Paint(PainterManager* _painter)
{
    float percent = _acumTime / _duration;

    _painter->AddToPaint(_sprite, _currentX, _currentY, 1 - percent);
}

