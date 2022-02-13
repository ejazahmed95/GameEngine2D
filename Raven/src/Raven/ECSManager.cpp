#include "ECSManager.h"
#include "Systems.h"
#include "Systems/BaseSystem.h"

namespace Raven {
	Core::Entity* ECSManager::CreateEntity() {
		const auto entity = new Core::Entity();
		GetECS()->m_AllEntities.insert({ entity->Id(), entity });
		return entity;
	}

	void ECSManager::OnComponentAdded(Types::t_uid entityId, Types::t_uid componentId) {

		auto entity = m_AllEntities[entityId];
		auto entityMask = entity->GetComponentMask();
		for (const auto & system : m_AllSystems) {
			BitMask systemCompMask = system->GetComponentMask();
			if(!systemCompMask.At(static_cast<int>(componentId))) {
				return;
			}

			if(entityMask.contains(systemCompMask)) {
				system->RegisterEntity(entity);
			}
		}
		
	}

	void ECSManager::OnComponentRemoved(Types::t_uid entityId, Types::t_uid componentId) {
		
	}

	void ECSManager::RegisterSystem(System::BaseSystem* system) {
		m_AllSystems.push_back(system);
	}

}
