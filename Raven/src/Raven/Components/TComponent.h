#pragma once
#include "../Core.h"
#include "../CoreModule/Types.h"

namespace Raven { namespace Components {
	struct ComponentId {
		static Types::t_Uid s_id;
		static Types::t_Uid Get();
	};

	struct RAVEN_API IComponent {
		
	};

	template <typename T>
	struct RAVEN_API TComponent: public IComponent {
		static Types::t_Uid Id() {
			static Types::t_Uid s_id = ComponentId::Get();
			return s_id;
		}
	};

	// template <typename T>
	// class ComponentManager {
	// public:
	// private:
	// 	std::map<Entity, TComponent<T>> components;
	// };
	//
	// class Entity {
	// 	Types::t_Uid id;
	// };
	//
	// class EntityWrapper {
	// 	Entity entity;
	//
	// public:
	// 	template<typename T>
	// 	void addComponent(TComponent<T> component) {
	// 		getComponentManager().addEntity();
	// 		
	// 	}
	//
	// 	template<typename T>
	// 	void removeComponent(TComponent<T> component) {
	// 		
	// 	}
	// };
	//
	// class ComponentWrapper {
	// 	
	// };
	//
	// void CreateEntity() {
	// 	
	// }
}}

