#include "GameBoard.h"

#include <SFML/Main.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/Util/TextureManager.h"

using namespace Game;

GameBoard::GameBoard()
{
    std::vector<std::string> words;
    words.push_back("air");
    words.push_back("water");
    words.push_back("earth");

    SpawnWords(words);

    m_dragging = nullptr;
}

GameBoard::~GameBoard()
{
}

void GameBoard::SpawnWords(std::vector<std::string> strs)
{
    m_words = 0;
    for (int j = 0; j < strs.size(); j++)
    {
        std::string s = strs[j];
        MakeWord(s);
    }

    MakeWall(100.f, 100.f, 5.f, 500.f);

    MakeBox(150, 200);
    MakeWord("K", 194, 185)->GetComponent<GameEngine::TextRenderComponent>()->SetFont("Arrows ADF.ttf");
    MakeBox(250, 200);
    MakeWord("=", 294, 185);
    MakeBox(350, 200);
    MakeWord("K", 394, 185)->GetComponent<GameEngine::TextRenderComponent>()->SetFont("Arrows ADF.ttf");
    MakeBox(450, 200);
}

void GameBoard::MakeBox(float x, float y)
{
    boxes.push_back(MakeWall(x, y, 75, 50));
    MakeWall(x, y, 71, 46, sf::Color::Black);
}

GameEngine::Entity *GameBoard::MakeWord(std::string word, int x, int y)
{
    GameEngine::Entity *ent = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);
    words.push_back(ent);

    ent->SetSize(sf::Vector2f(100.f, 20.f));
    if (x == -1)
    {
        ent->SetPos(sf::Vector2f(20.f, 20.f + m_words * 30));
        m_words++;
    }
    else
    {
        ent->SetPos(sf::Vector2f(x, y));
    }

    GameEngine::TextRenderComponent *render = ent->AddComponent<GameEngine::TextRenderComponent>();
    render->SetString(word);
    render->SetColor(sf::Color::White);
    render->SetFillColor(sf::Color::Transparent);
    render->SetCharacterSizePixels(18);
    render->SetFont("Bookerly-Regular.ttf");

    return ent;
}

GameEngine::Entity *GameBoard::MakeWall(float x, float y, float width, float height, sf::Color color)
{
    GameEngine::Entity *ent = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);

    ent->SetSize(sf::Vector2f(width, height));
    ent->SetPos(sf::Vector2f(x, y));

    GameEngine::RenderComponent *render = ent->AddComponent<GameEngine::RenderComponent>();
    render->SetFillColor(color);

    return ent;
}

void GameBoard::Update()
{
}

void GameBoard::HandleEvent(sf::Event event)
{
    // printf("Handling event %d\n", event.type);
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        // printf("pressed\n");
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;

            printf("a %d %d\n", x, y);

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
        // printf("moved \n");
        if (m_dragging)
        {
            int x = event.mouseMove.x;
            int y = event.mouseMove.y;

            m_dragging->SetPos(sf::Vector2f((x + 38.43569) / 1.61404 - 50, (y - 5.90485) / 1.19912 - 10));

            // printf("b %d %d\n", x, m_dragging->GetPos().x);
        }
        break;
    case sf::Event::MouseButtonReleased:
        // printf("released \n");
        if (m_dragging)
        {
            if (m_dragging->GetPos().x > 100 && CheckDragging())
            {
            }
            else
                GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_dragging);
        }

        m_dragging = nullptr;
        break;
    default:
        break;
    }
}

bool GameBoard::CheckDragging()
{
    sf::Vector2f dpos = m_dragging->GetPos();
    sf::Vector2f dsize = m_dragging->GetSize();

    for (GameEngine::Entity *word : boxes)
    {
        sf::Vector2f wpos = word->GetPos();
        sf::Vector2f wsize = word->GetSize();

        wpos.x -= 25;
        wpos.y -= 12;

        bool lx = wpos.x <= dpos.x && dpos.x <= wpos.x + wsize.x;
        bool rx = wpos.x <= dpos.x + dsize.x && dpos.x + dsize.x <= wpos.x + wsize.x;
        bool ty = wpos.y <= dpos.y && dpos.y <= wpos.y + wsize.y;
        bool by = wpos.y <= dpos.y + dsize.y && dpos.y + dsize.y <= wpos.y + wsize.y;

        if ((lx && ty) || (lx && by) || (rx && ty) || (rx && by))
        {
            m_dragging->SetPos(wpos);
            return true;
        }
    }
    return false;
}

void GameBoard::Merge(std::string a, std::string b)
{
    printf("merging %s %s\n", a.c_str(), b.c_str());
}
