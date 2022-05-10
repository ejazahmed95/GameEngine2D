#include "EnemySystem.h"

#include "Raven/Components/Transform.h"
#include "../Components/EnemyAIComp.h"
#include "Raven/CoreModule/Entity.h"
#include "../Attack.h"
#include "Raven/Systems.h"
#include "RavenStd/memory/StrongPointer.h"
#include "Raven/ECSManager.h"

namespace Systems {

	EnemySystem::EnemySystem() {
		// using namespace Raven::Components;
		m_Mask.Add(Raven::Components::Transform::Id());
		m_Mask.Add(Components::EnemyAIComp::Id());
	}

	void EnemySystem::Update(float dt) {
		if(playerRef == nullptr) playerRef = Raven::GetECS().AcquireOwnership()->GetEntityByName("Pikachu");
		if (playerRef->Destroyed()) return;
		for (const auto& element : m_RegisteredEntities) {
			if (element->Destroyed()) continue;
			// Launch Attacks towards the player
			auto enemyComp = element->GetComponent<Components::EnemyAIComp>();
			enemyComp->timeElapsed += dt;
			if(enemyComp->timeElapsed > enemyComp->attackInterval) {
				enemyComp->timeElapsed = 0;
				auto transform = element->GetComponent<Raven::Components::Transform>();
				auto pos = transform->Object2WorldMatrix() * Raven::Core::Point3D(0, 50, 0).ToVec4(1);
				auto rot = transform->Object2WorldMatrix() * Raven::Core::Point3D(0, 1, 0).ToVec4();
				auto dir = playerRef->GetComponent<Raven::Components::Transform>()->position;
				dir = dir - transform->position;
				
				auto attack = RavenStd::StrongPtr<Attack>(new Attack({ pos.X(), pos.Y(), pos.Z() }, dir, true));
			}
		}
	}
}
