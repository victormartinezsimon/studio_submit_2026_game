#include "ButtonA.h"
#include "InputManager.h"

ButtonA::ButtonA(InputManager *inputManager) : _inputManager(inputManager), _enabled(false) {}

void ButtonA::SelectInPosition(float duration, std::pair<int, int> marginA, std::pair<int, int> marginB, std::function<void(int)> callback)
{
    _duration = duration;
    _callback = callback;
    _isSelectInPosition = true;
    _enabled = true;

    _marginA = marginA;
    _marginB = marginB;
    _lastInputValue = -1;
    _acumTime = 0;
}

void ButtonA::SelectAfterTime(float duration, std::function<void(int)> callback)
{
    _duration = duration;
    _callback = callback;
    _isSelectInPosition = false;
    _enabled = true;
    _acumTime = 0;
}

void ButtonA::Update(float deltaTime)
{
    if (!_enabled)
    {
        return;
    }

    if (_isSelectInPosition)
    {
        UpdateSelectInPosition(deltaTime);
    }
    else
    {
        UpdateSelectAfterTime(deltaTime);
    }
}

void ButtonA::UpdateSelectInPosition(const float deltaTime)
{
    auto currentInputValue = _inputManager->GetInputValue();

    int selection = -1;
    if(_marginA.first <= currentInputValue && currentInputValue <= _marginA.second)
    {
        _acumTime += deltaTime;
        selection = 0;
    }
    else
    {
        if(_marginB.first <= currentInputValue && currentInputValue <= _marginB.second)
        {
            _acumTime += deltaTime;
            selection = 1;
        }
        else
        {
            selection = -1;
            _acumTime = 0;
        }
    }
    
    if(_acumTime >= _duration)
    {
        _callback(selection);
        _enabled = false;
    }

}
void ButtonA::UpdateSelectAfterTime(const float deltaTime)
{
    _acumTime += deltaTime;

    if (_acumTime > _duration)
    {
        auto value = _inputManager->GetInputValueNormalized();
        _callback(value <= 0.5f ? 0 : 1);
        _enabled = false;
    }
}