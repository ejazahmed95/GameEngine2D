#pragma once

#include <unordered_map>

#include "../Core.h"
#include <vector>
#include "../CoreModule/BitMask.h"

namespace Raven { namespace Core {
	class Entity;
}}

namespace Raven { namespace System {

	class RAVEN_API BaseSystem {
	public:
		BaseSystem();
		virtual ~BaseSystem() = default;
		void TryAddEntity(Core::Entity* entity);
		BaseSystem(const BaseSystem&) = delete;
		BaseSystem& operator=(const BaseSystem&) = delete;

		virtual void Initialize();
		virtual void Update(float dt) = 0;
		virtual void Destroy() = 0;
		BitMask& GetComponentMask() { return m_Mask; }

		void RegisterEntity(Core::Entity*);
		void RemoveEntity();
	protected:
		std::vector<Core::Entity*> m_RegisteredEntities;
		BitMask m_Mask;
	};
}}
