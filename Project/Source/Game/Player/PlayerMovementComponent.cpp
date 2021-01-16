#include "PlayerMovementComponent.h"

#include <SFML/Window/Keyboard.hpp>
#include "GameEngine/GameEngineMain.h"


using namespace Game;

void PlayerMovementComponent::Update() {
    Component::Update();
    
    float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();

    sf::Vector2f displacement{0.0f, 0.0f};

    float inputAmount = 100.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        displacement.x -= inputAmount * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        displacement.x += inputAmount * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        displacement.y += inputAmount * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        displacement.y -= inputAmount * deltaTime;
    }

    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}

void PlayerMovementComponent::OnAddToWorld() {

}