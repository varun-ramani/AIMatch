#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <random>

#include "WordVectors/ServerComm.h"

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
		GameEngine::Entity *MakeWord(std::string word, int x = -1, int y = -1, int fontsize = 10);
		void MakeBox(float x, float y);
		GameEngine::Entity *MakeWall(float x, float y, float width, float height, sf::Color color = sf::Color::White);
		bool IsGameOver() { return livesn == 0; }
		bool CheckDragging();
		void LoseLife();
		void Shake(int i);
		void MakeResult(std::string result);

	private:
		std::vector<GameEngine::Entity *> words;
		std::vector<GameEngine::Entity *> boxes;
		std::vector<GameEngine::Entity *> bboxes;
		GameEngine::Entity *dragged[3];
		GameEngine::Entity *lives[5];
		GameEngine::Entity *m_dragging;
		int m_words;
		WordVectors::ServerComm server = WordVectors::ServerComm("http://localhost:5000");
		int livesn = 5;

		int animframe = -1;
		int animmax = 1200;
		int anim[40] = {
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			-1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
		};

		GameEngine::Entity *result;
		int moveframe = -1;
		sf::Vector2f to;
		sf::Vector2f from;
		int mframes = 6000;
	};
} // namespace Game
