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

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			//mouse events
			case sf::Event::MouseButtonPressed:
				break;

			case sf::Event::MouseMoved:
				break;

			// we don't process other types of events
			default:
				break;
			}
		}
	}

	delete mainEngine;
	return 0;
}
