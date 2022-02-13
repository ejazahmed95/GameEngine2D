#pragma once
#include <map>
#include <vector>
#include "CoreModule/Entity.h"

namespace Raven { namespace System {
		class BaseSystem;
	}

	class ECSManager {
	public:
		static Core::Entity* CreateEntity();
		void OnComponentAdded(Types::t_uid entityId, Types::t_uid componentId);
		void OnComponentRemoved(Types::t_uid entityId, Types::t_uid componentId);
		void RegisterSystem(System::BaseSystem* system);
	private:
		std::vector<System::BaseSystem*> m_AllSystems;
		std::unordered_map<Types::t_uid, Core::Entity*> m_AllEntities;
		//std::unordered_map<Types::t_uid, std::vector<System::BaseSystem*>> m_SystemsMap;
	};
}
