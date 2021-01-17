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

void GameBoard::SpawnWords(std::vector<std::string> strs)
{
    int i = 0;
    for (int j = 0; j < strs.size(); j++)
    {
        std::string s = strs[j];
        MakeWord(s, 20.f, 20.f + i * 30);

        i++;
    }

    MakeWall(150.f, 100.f, 5.f, 500.f);
}

GameEngine::Entity *GameBoard::MakeWord(std::string word, float x, float y)
{
    GameEngine::Entity *ent = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);
    words.push_back(ent);

    ent->SetPos(sf::Vector2f(x, y));
    ent->SetSize(sf::Vector2f(100.f, 20.f));

    GameEngine::TextRenderComponent *render = ent->AddComponent<GameEngine::TextRenderComponent>();
    render->SetString(word);
    render->SetColor(sf::Color::White);
    render->SetFillColor(sf::Color::Transparent);
    render->SetCharacterSizePixels(20);
    render->SetFont("Bookerly-Regular.ttf");

    return ent;
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
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;

            int i = 1;
            for (GameEngine::Entity *word : words)
            {
                sf::Vector2f pos = word->GetPos();
                sf::Vector2f size = word->GetSize();

                if ((pos.x) <= x && x <= (pos.x + size.x) && (pos.y + i * 10) <= y && y <= (pos.y + size.y + i * 10))
                {
                    std::string s = word->GetComponent<GameEngine::TextRenderComponent>()->GetString().getString();
                    m_dragging = MakeWord(s, pos.x, pos.y);
                }

                i++;
            }
        }
        break;
    case sf::Event::MouseMoved:
        if (m_dragging)
        {
            int x = event.mouseMove.x;
            int y = event.mouseMove.y;

            m_dragging->SetPos(sf::Vector2f(x, y));
        }
        break;
    case sf::Event::MouseButtonReleased:
        m_dragging = nullptr;
        break;
    default:
        break;
    }
}