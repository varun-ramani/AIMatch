#include "GameBoard.h"

#include <SFML/Main.hpp>

#include "GameEngine/GameEngineMain.h"
#include "Game/Player/PlayerMovementComponent.h"

using namespace Game;

GameBoard::GameBoard()
{
    SpawnPlayer();
}

GameBoard::~GameBoard()
{
}

void GameBoard::SpawnPlayer()
{
    m_player = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

    m_player->SetPos(sf::Vector2(50.f, 50.f));
    m_player->SetSize(sf::Vector2(50.f, 50.f));

    GameEngine::RenderComponent* render = m_player->AddComponent<GameEngine::RenderComponent>();
    Game::PlayerMovementComponent* movementComponent = m_player->AddComponent<Game::PlayerMovementComponent>();
}

void GameBoard::Update()
{

}