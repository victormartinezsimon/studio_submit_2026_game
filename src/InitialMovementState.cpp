#include "InitialMovementState.h"
#include "PainterManager.h"
#include "Plane.h"
#include "GameConfig.h"
#include "EasingManager.h"
#include "RandomManager.h"

InitialMovementState::InitialMovementState(Plane *player, PainterManager *painter, 
        NumberManager* numberManager, 
        EasingManager* easingManager, RandomManager* randomManager, ButtonA* buttonAManager,
		 Pool<Plane, PLANES_POOL_SIZE>* enemiesPool) : 
State(player, painter, numberManager, 
			easingManager, randomManager, buttonAManager), _enemiesPool(enemiesPool)
{
}

State::STATES InitialMovementState::Update(const float deltaTime, float _currentFrameInputValueNormalized)
{
	return _nextState;
}
void InitialMovementState::Paint()
{
	_player->Paint(_painterManager);
	_enemiesPool->Paint(_painterManager);
}

void InitialMovementState::PaintUI(){}

void InitialMovementState::OnEnter()
{
	_nextState = STATES::INITIAL_MOVEMENT;

	_player->SetPositionY(POSITION_Y_PLAYER);
	_player->SetPlayerTeam(TEAM_PLAYER);
	_player->ConfigureSprite(_painterManager);

	int totalEnemies = _enemiesPool->TotalInUse();

	float startX = -1;
	float startY = -1;
	if(totalEnemies <= MAX_ENEMIES_PER_ROW )
	{
		startX = SCREEN_WIDTH / 2;
		startY =  SCREEN_HEIGHT / 2;
	}

	int randomStart = _randomManager->GetNextIntValue();

	_enemiesPool->for_each_active(
		[&](Plane &p)
		{
			p.SetPlayerTeam(TEAM_ENEMY);
			p.ConfigureSprite(_painterManager);

			if(startX == -1 && startY == -1)
			{
				int zone = (randomStart + p.GetID()) % 3;
				switch(zone)
				{
					default:
					case 0://top
						startX = _randomManager->GetValue(0, SCREEN_WIDTH);
						startY = 0 - static_cast<int>(p.GetHeight());
						break;
					case 1://left
						startY = _randomManager->GetValue(0, SCREEN_HEIGHT/2);
						startX = 0 - static_cast<int>(p.GetWidth());
						break;
					case 2:
						startY = _randomManager->GetValue(0, SCREEN_HEIGHT/2);
						startX = SCREEN_WIDTH + static_cast<int>(p.GetWidth());
						break;
				}
			}

			_easingManager->AddEase(INTIAL_ANIMATION_DURATION, startX, startY,
				p.GetX(), p.GetY(), Ease::EASE_TYPES::INOUTCUBE, 
				[this] (bool normalEnded, int noUsed)
				{
					_nextState = STATES::BATTLE;
				}, 
				[&p](float x, float y, Ease& ease, float percent)	{ p.SetPosition(x, y); }
			);
		}
	);
}
void InitialMovementState::OnExit()
{
}