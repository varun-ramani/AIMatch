#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"

#include <vector>

int main()
{
	GameEngine::GameEngineMain *mainEngine = GameEngine::GameEngineMain::GetInstance();

	// TODO: Check if server connection available on startup instead of crashing later.
	// WordVectors::ServerComm serverComm("https://localhost:5000");

	sf::Window *window = mainEngine->GetRenderWindow();
	window->create(sf::VideoMode(1600, 1200), "AIMatch", sf::Style::Titlebar | sf::Style::Close);

	while (mainEngine->GetRenderWindow()->isOpen())
	{
		mainEngine->Update();
	}

	delete mainEngine;
	return 0;
}
