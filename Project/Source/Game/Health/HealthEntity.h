#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/Health/HealthChangeComponent.h"

namespace Game
{

	class HealthEntity : public GameEngine::Entity
	{
	public:
		HealthEntity();
		~HealthEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;	
		Game::HealthChangeComponent*	m_healthChangeComponent;
		GameEngine::AnimationComponent* m_animComponent;
	};
}

