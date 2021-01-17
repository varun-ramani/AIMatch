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
    words.push_back("man");
    words.push_back("woman");
    words.push_back("king");

    SpawnWords(words);

    MakeWall(100.f, 100.f, 5.f, 500.f);

    MakeBox(150, 200);
    MakeWord("K", 194, 185, 20)->GetComponent<GameEngine::TextRenderComponent>()->SetFont("Arrows ADF.ttf");
    MakeBox(250, 200);
    MakeWord("=", 294, 185, 20);
    MakeBox(350, 200);
    MakeWord("K", 394, 185, 20)->GetComponent<GameEngine::TextRenderComponent>()->SetFont("Arrows ADF.ttf");
    MakeBox(450, 200);

    for (int i = 0; i < 3; i++)
    {
        dragged[i] = nullptr;
    }

    m_dragging = nullptr;

    for (int i = 0; i < 5; i++)
    {
        lives[i] = new GameEngine::Entity();
        GameEngine::GameEngineMain::GetInstance()->AddEntity(lives[i]);
        GameEngine::SpriteRenderComponent *r = lives[i]->AddComponent<GameEngine::SpriteRenderComponent>();
        r->SetTexture(GameEngine::eTexture::Life);
        r->SetZLevel(2);
        lives[i]->SetPos(sf::Vector2f(150 + i * 50, 50));
        lives[i]->SetSize(sf::Vector2f(50, 50));
    }
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
}

void GameBoard::MakeBox(float x, float y)
{
    boxes.push_back(MakeWall(x, y, 75, 50));
    bboxes.push_back(MakeWall(x, y, 71, 46, sf::Color::Black));
}

GameEngine::Entity *GameBoard::MakeWord(std::string word, int x, int y, int fontsize)
{
    GameEngine::Entity *ent = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);

    ent->SetSize(sf::Vector2f(50.f, 10.f));
    if (x == -1)
    {
        ent->SetPos(sf::Vector2f(20.f, 20.f + m_words * 15));
        m_words++;
        words.push_back(ent);
    }
    else
    {
        ent->SetPos(sf::Vector2f(x, y));
    }

    GameEngine::TextRenderComponent *render = ent->AddComponent<GameEngine::TextRenderComponent>();
    render->SetString(word);
    render->SetColor(sf::Color::White);
    render->SetFillColor(sf::Color::Transparent);
    render->SetCharacterSizePixels(fontsize);
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
    if (animframe != -1)
    {
        animframe++;
        if (animframe % 10 == 0)
        {
            Shake(anim[(animframe / 10) % 40]);
            if (animframe > animmax)
            {
                animframe = -1;
            }
        }
    }
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

            x = x - 50;
            y = y - 44;

            // printf("a %d %d\n", x, y);

            int i = 0;
            for (GameEngine::Entity *word : words)
            {
                sf::Vector2f pos = word->GetPos();
                sf::Vector2f size = word->GetSize();

                if ((pos.x) <= x && x <= (pos.x + size.x) && (pos.y + i * 20) <= y && y <= (pos.y + size.y + i * 20))
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

            m_dragging->SetPos(sf::Vector2f((x - 142.65194) / 3.2127 + 35, (y - 75.56521) / 2.44906 + 25));
            // m_dragging->SetPos(sf::Vector2f(x, y));

            // printf("b %f %f\n", m_dragging->GetPos().x, m_dragging->GetPos().y);
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

    int i = 0;
    for (GameEngine::Entity *word : boxes)
    {
        if (i == 3)
            return false;

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
            if (dragged[i] != nullptr)
            {
                GameEngine::GameEngineMain::GetInstance()->RemoveEntity(dragged[i]);
            }
            dragged[i] = m_dragging;
            if (dragged[0] != nullptr && dragged[1] != nullptr && dragged[2] != nullptr)
            {
                std::string a = dragged[0]->GetComponent<GameEngine::TextRenderComponent>()->GetString().getString();
                std::string b = dragged[1]->GetComponent<GameEngine::TextRenderComponent>()->GetString().getString();
                std::string c = dragged[2]->GetComponent<GameEngine::TextRenderComponent>()->GetString().getString();

                std::string result = server.getWordAnalogy(a, b, c);
                printf("Got back %s\n", result.c_str());

                for (int q = 0; q < 3; q++)
                {
                    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(dragged[q]);
                    dragged[q] = nullptr;
                }
                return true;
            }
            m_dragging->SetPos(wpos);

            return true;
        }
        i++;
    }
    return false;
}

void GameBoard::LoseLife()
{
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(lives[livesn-- - 1]);

    if (livesn == 0)
    {
        printf("Game over!\n");
    }

    animframe = 0;
}

void GameBoard::Shake(int i)
{
    for (auto box : boxes)
    {
        float x = box->GetPos().x;
        float y = box->GetPos().y;

        box->SetPos(sf::Vector2f(x + i, y));
    }

    for (auto box : bboxes)
    {
        float x = box->GetPos().x;
        float y = box->GetPos().y;

        box->SetPos(sf::Vector2f(x + i, y));
    }
}