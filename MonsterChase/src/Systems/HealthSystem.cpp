#include "HealthSystem.h"
#include "../Components/HealthComponent.h"
#include "Raven/CoreModule/Entity.h"

namespace Systems {

	HealthSystem::HealthSystem() : m_EnemyDeadCount(0), m_PlayerDeadCount(0){
		m_Mask.Add(Components::HealthComponent::Id());
	}

	void HealthSystem::Update(float dt) {
		for (const auto& element : m_RegisteredEntities) {
			// Launch Attacks towards the player
			if(element->Destroyed()) continue;
			auto healthComp = element->GetComponent<Components::HealthComponent>();

			if (healthComp->health <= 0) {
				element->Destroy();
				if (element->GetTag() == "Player") {
					m_PlayerDeadCount++;
				} else if(element->GetTag() == "Enemy") {
					m_EnemyDeadCount++;
				}
			}
		}
	}
}
