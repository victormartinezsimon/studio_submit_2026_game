#include "ButtonA.h"
#include "GameConfig.h"

constexpr int selectionA = 0;
constexpr int selectionB = 1;
constexpr int selectionNone = -1;

void ButtonA::SelectInPosition(float duration, std::pair<int, int> optionA, std::function<void(int)> callback)
{
    SelectInPosition(duration, optionA, {-1, -1}, callback);
}

void ButtonA::SelectInPosition(float duration, std::pair<int, int> optionA, std::pair<int, int> optionB, std::function<void(int)> callback)
{
    _duration = duration;
    _callback = callback;
    _enabled = true;

    _optionA = optionA;
    _optionB = optionB;
    _acumTime = 0;
    _currentSelection = selectionNone;
}

void ButtonA::Update(float deltaTime, const float currentInputValueNormalized)
{
    if (!_enabled)
    {
        return;
    }

    float screenValue = SCREEN_WIDTH * currentInputValueNormalized;
    if (_optionA.first <= screenValue && screenValue <= _optionA.second)
    {
        if (_currentSelection == selectionA)
        {
            _acumTime += deltaTime;
        }
        _currentSelection = selectionA;
    }
    else
    {
        if (_optionB.first <= screenValue && screenValue <= _optionB.second)
        {
            if (_currentSelection == selectionB)
            {
                _acumTime += deltaTime;
            }
            _currentSelection = selectionB;
        }
        else
        {
            _acumTime = 0;
        }
    }

    if (_acumTime >= _duration)
    {
        _callback(_currentSelection);
        _enabled = false;
    }
}

float ButtonA::GetLeftTime() const
{
    return _duration - _acumTime;
}
