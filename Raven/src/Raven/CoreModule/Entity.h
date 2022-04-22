#pragma once
#include "../Components/TComponent.h"
#include <unordered_map>

#include "BitMask.h"

namespace Raven { namespace Core {

	class Entity {
	public:
		Entity() : m_Id(++s_EntityCount) {}
		~Entity();

		template<class T>
		bool AddComponent(Components::TComponent<T>* component) {
			auto id = Components::TComponent<T>::Id();
			if(m_Components.find(id) != m_Components.end()) {
				return false;
			}
			m_Components.insert({ id, component });
			componentMask.Add(id);
			this->componentAdded(id);
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
		T* GetComponent() {
			auto id = Components::TComponent<T>::Id();
			if(m_Components.find(id) == m_Components.end()) {
				return nullptr;
			}
			return dynamic_cast<T*>(m_Components[id]);
		}

		void SetName(std::string name) {
			// std::move(name, m_Name);
			m_Name = name;
		}

		std::string GetName() const { return m_Name; }


		static int s_EntityCount;

		Types::t_uid Id() const { return m_Id; }
		BitMask& GetComponentMask() { return componentMask; }
		void componentAdded(Types::t_uid) const;
	private:
		void componentAdded2(Types::t_uid) const;
	private:
		int m_Id;
		std::string m_Name;
		std::unordered_map<Types::t_uid, Components::IComponent*> m_Components;
		BitMask componentMask;
	};
}}
