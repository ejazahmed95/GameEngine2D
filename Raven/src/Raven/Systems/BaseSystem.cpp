#include "BaseSystem.h"
#include "../CoreModule/Entity.h"

namespace Raven { namespace System {

	void BaseSystem::RegisterEntity(Core::Entity* entity) {
		m_RegisteredEntities.push_back(entity);
	}

	void BaseSystem::RemoveEntity() {
		// todo: Won't be needed when using weak pointers
	}
}}