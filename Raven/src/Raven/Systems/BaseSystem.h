#pragma once

#include "../Core.h"
#include <vector>

namespace Raven { namespace Core {
	class Entity;
}}

namespace Raven { namespace System {

	class RAVEN_API BaseSystem {
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;
		BaseSystem(const BaseSystem&) = delete;
		BaseSystem& operator=(const BaseSystem&) = delete;

		virtual void Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Destroy() = 0;

		// Virtual methods
		void RegisterEntity(Core::Entity*);
		void RemoveEntity();
	private:
		std::vector<Core::Entity*> m_RegisteredEntities;
	};
}}
