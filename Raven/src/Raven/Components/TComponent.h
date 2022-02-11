#pragma once
#include "../Core.h"
#include "../CoreModule/Types.h"

namespace Raven { namespace Components {
	struct ComponentId {
		static Types::t_id s_id;
		static Types::t_id Get();
	};

	template <typename T>
	class RAVEN_API TComponent {
		static Types::t_id Id() {
			static Types::t_id s_id = ComponentId::Get();
			return s_id;
		}
	};

	template <typename T>
	class ComponentManager {
	public:
	private:
		std::unordered_<Entity, TComponent<T>> components;
	};

	class Entity {
		Types::t_id id;
	};

	class EntityWrapper {
		Entity entity;

	public:
		template<typename T>
		void addComponent(TComponent<T> component) {
			getComponentManager().addEntity();
			
		}

		template<typename T>
		void removeComponent(TComponent<T> component) {
			
		}
	};

	class ComponentWrapper {
		
	};

	void CreateEntity() {
		
	}
}}

