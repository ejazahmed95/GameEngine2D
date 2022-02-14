#include "BaseSystem.h"

#include "../ECSManager.h"
#include "../CoreModule/Entity.h"
#include "../Systems.h"
#include <typeinfo>

namespace Raven { namespace System {

	BaseSystem::BaseSystem() {
		GetECS()->RegisterSystem(this);
	}

	void BaseSystem::Initialize() {
		SLib::Log::D("Initializing " + std::string(typeid(*this).name()));
	}

	void BaseSystem::Destroy() {
		SLib::Log::D("Destroying " + std::string(typeid(*this).name()));
	}

	void BaseSystem::RegisterEntity(Core::Entity* entity) {
		SLib::Log::D(std::string(typeid(*this).name())+ " Registered Entity::" + std::to_string(entity->Id()));
		m_RegisteredEntities.push_back(entity);
	}

	void BaseSystem::RemoveEntity() {
		// todo: Won't be needed when using weak pointers
	}
}}
