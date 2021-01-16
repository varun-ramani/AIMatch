#include "GameBoard.h"

#include <SFML/Main.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"

using namespace Game;

GameBoard::GameBoard()
{
    std::vector<std::string> words;
    words.push_back("air");
    words.push_back("water");
    words.push_back("earth");

    SpawnWords(words);
}

GameBoard::~GameBoard()
{
}

void GameBoard::SpawnWords(std::vector<std::string> words)
{
    int i = 0;
    for (int j = 0; j < words.size(); j++)
    {
        std::string s = words[j];

        m_player = new GameEngine::Entity();
        GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

        m_player->SetPos(sf::Vector2f(50.f, 50.f + i * 60));
        m_player->SetSize(sf::Vector2f(100.f, 50.f));

        GameEngine::TextRenderComponent *render = m_player->AddComponent<GameEngine::TextRenderComponent>();
        render->SetString(s);
        render->SetColor(sf::Color::White);
        render->SetFillColor(sf::Color::Black);
        render->SetCharacterSizePixels(20);
        render->SetFont("Bookerly-Regular.ttf");

        std::cout << s;

        i++;
    }
}

void GameBoard::Update()
{
}