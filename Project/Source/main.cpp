#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"

#include <vector>

int main()
{
	GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
    
	while (mainEngine->GetRenderWindow()->isOpen())
	{				
		mainEngine->Update();
	}

	delete mainEngine;
	return 0;
}
