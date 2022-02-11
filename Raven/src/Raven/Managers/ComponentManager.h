#pragma once
#include <map>

namespace Raven { namespace Manager {

	template<typename T>
	class ComponentManager {
	public:
	private:
		std::map<Entity, TComponent<T>> components;
	};
}}
