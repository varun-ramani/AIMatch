#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application
	class PlayerEntity;

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();
		void HandleEvent(sf::Event event);

		void SpawnWords(std::vector<std::string> words);
		void MakeWall(float x, float y, float width, float height);
		bool IsGameOver() const { return m_isGameOver; }

	private:
		std::vector<GameEngine::Entity *> words;
		GameEngine::Entity *m_dragging;

		void CreateHealth();
		void UpdateHealth();
		
		GameEngine::Entity *m_player;
		GameEngine::Entity* m_health;
		bool  m_isGameOver;
	};
} // namespace Game
