#include "ECSManager.h"
#include "Systems.h"
#include "Systems/BaseSystem.h"
#include <typeinfo>

#include "RavenStd/Logger.h"

namespace Raven {
	ECSManager::~ECSManager() {
		for (const auto & entity : m_AllEntities) {
			delete entity.second;
		}
	}

	void ECSManager::Initialize() const {
		for (const auto& system : m_AllSystems) {
			system->Initialize();
		}
	}

	Core::Entity* ECSManager::CreateEntity() {
		const auto entity = new Core::Entity();
		GetECS().AcquireOwnership()->m_AllEntities.insert({ entity->Id(), entity });
		return entity;
	}

	void ECSManager::OnComponentAdded(Types::t_uid entityId, Types::t_uid componentId) {
		auto entity = m_AllEntities[entityId];
		RavenStd::Log::D("Component Added:: Entity[" + entity->GetName() + "] = " + std::to_string(entityId) + " | ComponentId = " + std::to_string(componentId));
		auto entityMask = entity->GetComponentMask();
		for (const auto & system : m_AllSystems) {
			BitMask systemCompMask = system->GetComponentMask();
			if(!systemCompMask.At(static_cast<int>(componentId))) {
				continue;
			}

			if(entityMask.contains(systemCompMask)) {
				system->RegisterEntity(entity);
			}
		}
	}

	void ECSManager::OnComponentRemoved(Types::t_uid entityId, Types::t_uid componentId) {
		
	}

	void ECSManager::RegisterSystem(System::BaseSystem* system) {
		RavenStd::Log::I("New System Registered: " + std::string(typeid(*system).name()));
		m_AllSystems.push_back(system);
	}

	void ECSManager::Update(float delta) const {
		for (const auto & system : m_AllSystems) {
			system->Update(delta);
		}
	}

	void ECSManager::Shutdown() const {
		for (size_t i = m_AllSystems.size() - 1; i > 0; --i) {
			m_AllSystems[i]->Destroy();
		}
	}

	Core::Entity* ECSManager::GetEntityByName(const std::string& name) const {
		for (const auto& entity : m_AllEntities) {
			if(entity.second->GetName() == name) {
				return entity.second;
			}
		}
		RavenStd::Log::E("Could not find entity with name = " + name);
		return nullptr;
	}

}
