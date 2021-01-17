#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
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
		GameEngine::Entity *MakeWord(std::string word, int x = -1, int y = -1);
		void MakeBox(float x, float y);
		GameEngine::Entity *MakeWall(float x, float y, float width, float height, sf::Color color = sf::Color::White);
		bool IsGameOver() { return false; }
		void CheckDragging();
		void Merge(std::string a, std::string b);

	private:
		std::vector<GameEngine::Entity *> words;
		std::vector<GameEngine::Entity *> dragged;
		GameEngine::Entity *m_dragging;
		int m_words;
	};
} // namespace Game
