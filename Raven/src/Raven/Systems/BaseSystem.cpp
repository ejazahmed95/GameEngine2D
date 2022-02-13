#include "BaseSystem.h"

#include "../ECSManager.h"
#include "../CoreModule/Entity.h"
#include "../Systems.h"

namespace Raven { namespace System {

	BaseSystem::BaseSystem() {
		GetECS()->RegisterSystem(this);
	}

	void BaseSystem::Initialize() {
		
	}

	void BaseSystem::RegisterEntity(Core::Entity* entity) {
		m_RegisteredEntities.push_back(entity);
	}

	void BaseSystem::RemoveEntity() {
		// todo: Won't be needed when using weak pointers
	}
}}