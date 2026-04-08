#pragma once
#include "State.h"
#include <functional>
#include <string>
#include <unordered_map>
#include "PainterManager.h"

class ButtonA;
class NumberManager;

class ImprovementSelectionState: public State
{
    public:
        ImprovementSelectionState(Plane *player, PainterManager *painter, 
        NumberManager* numberManager, 
        EasingManager* easingManager, RandomManager* randomManager, ButtonA* buttonAManager, 
            std::function<void(const ImprovementID& optionForPlayer,const ImprovementID& optionForEnemy )> callbackSeleccion);
        
    public:    
        STATES Update(const float deltaTime, float currentFrameInputValueNormalized)override;
        void Paint()override;
        void PaintUI()override;
        void OnEnter()override;
        void OnExit()override;

    public:
        void Configure(ImprovementID leftSelection, ImprovementID rightSelection);
    private:
        void InitializeImprovementsUI();

    private:
        STATES _nextState;
        float _currentFrameInputValueNormalized;
        std::function<void(const ImprovementID& optionForPlayer,const ImprovementID& optionForEnemy)> _callbackSeleccion;
        ImprovementID _leftSelection;
        ImprovementID _rightSelection;
        std::unordered_map<ImprovementID, PainterManager::SPRITE_ID> _improvementsUI;
        bool _doingFadeOut = false;
        float _percentEase = 1.0;
};