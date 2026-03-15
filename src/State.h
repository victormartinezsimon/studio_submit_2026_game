#pragma once

class Plane;
class PainterManager;
class ButtonA;

class State
{
public:
    enum class STATES
    {
        MENU,
        BATTLE,
        IMPROVEMENT_SELECTOR,
        INITIAL_MOVEMENT,
        HIGH_SCORE
    };

public:
    State(Plane *player, PainterManager *painter, ButtonA *buttonAManager)
        : _player(player), _painterManager(painter), _buttonAManager(buttonAManager) {};

public:
    virtual STATES Update(const float deltaTime, float _currentFrameInputValueNormalized,
                        int _currentFrameInputValue) {return STATES::MENU;};
    virtual void Paint() {};
    virtual void OnEnter() {};
    virtual void OnExit() {};

protected:
    Plane *_player;
    PainterManager *_painterManager;
    ButtonA *_buttonAManager;
};