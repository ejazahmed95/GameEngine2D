#include "Entity.h"

#include "../ECSManager.h"
#include "../Systems.h"

namespace Raven { namespace Core {

	int Entity::s_EntityCount = 0;

	Entity::~Entity() {
		for (const auto & component : m_Components) {
			delete component.second;
		}
	}

	void Entity::componentAdded(Types::t_uid componentId) const {
		GetECS()->OnComponentAdded(m_Id, componentId);
	}

	void Entity::componentAdded2(Types::t_uid) const {
		// do absolutely nothing
	}

}
}
