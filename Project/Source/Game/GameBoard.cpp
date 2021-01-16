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

        GameEngine::Entity *ent = new GameEngine::Entity();
        GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);

        ent->SetPos(sf::Vector2f(20.f, 20.f + i * 30));
        ent->SetSize(sf::Vector2f(100.f, 20.f));

        GameEngine::TextRenderComponent *render = ent->AddComponent<GameEngine::TextRenderComponent>();
        render->SetString(s);
        render->SetColor(sf::Color::White);
        render->SetFillColor(sf::Color::Black);
        render->SetCharacterSizePixels(20);
        render->SetFont("Bookerly-Regular.ttf");

        // std::cout << s;
        // std::cout << "\n";

        i++;
    }

    // MakeWall(75.f, 15.f, 130.f, 5.f);
    // MakeWall(75.f, 215.f, 130.f, 5.f);
    // MakeWall(15.f, 100.f, 5.f, 200.f);
    MakeWall(150.f, 100.f, 5.f, 500.f);

    // std::cout << sf::Mouse::getPosition().x;
    // std::cout << "\n";
}

void GameBoard::MakeWall(float x, float y, float width, float height)
{
    GameEngine::Entity *ent = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);

    ent->SetPos(sf::Vector2f(x, y));
    ent->SetSize(sf::Vector2f(width, height));

    GameEngine::RenderComponent *render = ent->AddComponent<GameEngine::RenderComponent>();
    render->SetFillColor(sf::Color::White);
}

void GameBoard::Update()
{
}

void GameBoard::HandleEvent(sf::Event event)
{
    std::cout << "hi\n";
}