#include "HealthEntity.h"

#include "GameEngine/Util/AnimationManager.h"

using namespace Game;

HealthEntity::HealthEntity()
{
	//Change
	m_healthChangeComponent = AddComponent<HealthChangeComponent>();

	//Render 
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();	
	m_renderComponent->SetTexture(GameEngine::eTexture::Health);
	m_renderComponent->SetZLevel(2);

	//Animation
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
}

 
HealthEntity::~HealthEntity()
{

}


void HealthEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void HealthEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
