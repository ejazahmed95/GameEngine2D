#include "Entity.h"

#include "../ECSManager.h"
#include "../Systems.h"

namespace Raven { namespace Core {

	int Entity::s_EntityCount = 0;

	void Entity::componentAdded(Types::t_uid componentId) const {
		GetECS()->OnComponentAdded(m_Id, componentId);
	}
}
}
