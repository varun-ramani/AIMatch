#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"

#include <vector>

int main()
{
	GameEngine::GameEngineMain *mainEngine = GameEngine::GameEngineMain::GetInstance();

	sf::Window *window = mainEngine->GetRenderWindow();
	window->create(sf::VideoMode(800, 600), "Glovechemy", sf::Style::Default);

	while (mainEngine->GetRenderWindow()->isOpen())
	{
		mainEngine->Update();
	}

	delete mainEngine;
	return 0;
}
