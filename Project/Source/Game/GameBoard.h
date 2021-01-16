#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/System/Vector2.hpp>
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
			void SpawnPlayer();
			bool IsGameOver() { return false; }

		private:
			GameEngine::Entity* m_player;

	};
} // namespace Game
