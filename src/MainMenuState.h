#pragma once
#include "State.h"

class MainMenuState: public State
{
    public:
        MainMenuState(Plane* player, PainterManager* painter, ButtonA* buttonAManager);
        
    public:    
        STATES Update(const float deltaTime, float _currentFrameInputValueNormalized,
	                        int _currentFrameInputValue)override;
        void Paint()override;
        void OnEnter()override;
        void OnExit()override;

    private:
        STATES _nextState;
};