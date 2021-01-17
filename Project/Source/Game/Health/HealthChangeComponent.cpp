#include "HealthChangeComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/AnimationManager.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;


void HealthChangeComponent::Update() {
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

void HealthChangeComponent::OnAddToWorld() {

}