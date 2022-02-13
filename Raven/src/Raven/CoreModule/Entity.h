#pragma once
#include "../Components/TComponent.h"
#include <unordered_map>

#include "BitMask.h"
#include "IComponent.h"

namespace Raven { namespace Core {

	class Entity {
	public:
		Entity() : m_Id(++s_EntityCount) {}

		template<class T>
		bool AddComponent(Components::TComponent<T>* component) {
			auto id = Components::TComponent<T>::Id();
			if(m_Components.find(id) != m_Components.end()) {
				return false;
			}
			m_Components.insert({ id, component });
			componentMask.Add(id);
			componentAdded(id);
			return true;
		}

		template<class T>
		bool RemoveComponent() {
			auto id = Components::TComponent<T>::Id();
			if (m_Components.find(id) == m_Components.end()) {
				return false;
			}
			m_Components.erase(id);
			return true;
		}

		template<class T>
		Components::TComponent<T>* GetComponent() {
			auto id = Components::TComponent<T>::Id();
			if(m_Components.find(id) == m_Components.end()) {
				return nullptr;
			}
			return static_cast<Components::TComponent<T>*>(m_Components[id]);
		}

		static int s_EntityCount;

		Types::t_uid Id() const { return m_Id; }
		BitMask& GetComponentMask() { return componentMask; }
	private:
		void componentAdded(Types::t_uid) const;
	private:
		int m_Id;
		std::unordered_map<Types::t_uid, IComponent*> m_Components;
		BitMask componentMask;
	};
}}
