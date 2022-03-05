#include "BaseSystem.h"

#include "../ECSManager.h"
#include "../CoreModule/Entity.h"
#include "../Systems.h"
#include <typeinfo>

#include "RavenStd/Logger.h"


namespace Raven { namespace System {

	BaseSystem::BaseSystem() {
		GetECS()->RegisterSystem(this);
	}

	void BaseSystem::Initialize() {
		RavenStd::Log::D("Initializing " + std::string(typeid(*this).name()));
	}

	void BaseSystem::Destroy() {
		RavenStd::Log::D("Destroying " + std::string(typeid(*this).name()));
	}

	void BaseSystem::RegisterEntity(Core::Entity* entity) {
		RavenStd::Log::D(std::string(typeid(*this).name())+ " Registered Entity::" + std::to_string(entity->Id()));
		m_RegisteredEntities.push_back(entity);
	}

	void BaseSystem::RemoveEntity() {
		// todo: Won't be needed when using weak pointers
	}
}}
