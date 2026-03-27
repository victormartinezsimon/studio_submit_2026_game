#include <iostream>
#include <thread>
#include <chrono>

#include "GameConfig.h"
#include "Pool.h"
#include "Bullet.h"
#include "Plane.h"
#include "InputManager.h"
#include "GameManager.h"
#include "PainterManager.h"
#include "SoundManager.h"
#include "Painter.h"
#include "Profiler.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	InputManager *inputManager = new InputManager();
	PainterManager* painterManager = new PainterManager();
	GameManager *gm = new GameManager(inputManager, painterManager);

	struct SPPlatform* platform = painterManager->GetPainter()->GetPlatform();

	
	float deltaTime = 0;
	
	auto lastTime = std::chrono::high_resolution_clock::now();
	
	bool ended = false;
	
	SoundManager* soundManager = new SoundManager(platform);
	#ifndef DEBUG
	soundManager->Prepare();
	#endif

	while (!ended)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count(); // seconds
    	lastTime = currentTime;

		ended = gm->Update(deltaTime);
		gm->Paint();
		painterManager->Paint();
		#ifndef DEBUG
		soundManager->Update();
		#endif
	}

	PROFILE_SAVE();
	soundManager->Shutdown();

	delete soundManager;
	delete inputManager;
	delete painterManager;
	delete gm;
}