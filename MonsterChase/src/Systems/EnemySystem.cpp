#include "EnemySystem.h"

#include "Raven/Components/Transform.h"
#include "../Components/EnemyAIComp.h"
#include "Raven/CoreModule/Entity.h"

namespace Systems {

	EnemySystem::EnemySystem() {
		// using namespace Raven::Components;
		m_Mask.Add(Raven::Components::Transform::Id());
		m_Mask.Add(Components::EnemyAIComp::Id());
	}

	void EnemySystem::Update(float dt) {
		for (const auto& element : m_RegisteredEntities) {
			if (element->Destroyed()) continue;
			// Launch Attacks towards the player
		}
	}
}
