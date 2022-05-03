#include "CollisionSystem2D.h"
#include "../CoreModule/Entity.h"

namespace Raven { namespace System {

	CollisionSystem2D::CollisionSystem2D() {
		using namespace Components;
		m_Mask.Add(Transform::Id());
		m_Mask.Add(Collider2D::Id());
	}

	void CollisionSystem2D::Update(float dt) {
		for (int i = 0; i < m_RegisteredEntities.size(); i++) {
			const auto element1 = m_RegisteredEntities[i];
			const auto collider1 = element1->GetComponent<Components::Collider2D>();
			const auto transform1 = element1->GetComponent<Components::Transform>();
			for (int j = i+1; j < m_RegisteredEntities.size(); j++) {
				const auto element2 = m_RegisteredEntities[j];
				const auto collider2 = element2->GetComponent<Components::Collider2D>();
				auto transform2 = element2->GetComponent<Components::Transform>();

				if(checkCollision(collider1, transform1, collider2, transform2)) {
					collider1->OnCollisionEnterCb(element2);
					collider2->OnCollisionEnterCb(element1);
				}
			}
		}
	}

	bool CollisionSystem2D::checkCollision(Components::Collider2D* collider1, Components::Transform* transform1,
		Components::Collider2D* collider2, Components::Transform* transform2) {

		if((transform1->position - transform2->position).Mag() < 20) {
			return true;
		}
		return false;
	}

}
}
