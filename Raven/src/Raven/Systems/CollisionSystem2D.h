#pragma once
#include "BaseSystem.h"
#include "../Components/Collider2D.h"

namespace Raven { namespace System {

	class RAVEN_API CollisionSystem2D : public BaseSystem {
	public:
		CollisionSystem2D();

		void Update(float dt) override;

	private:
		bool checkCollision(Core::Entity* element1, Core::Entity* element2, Components::Collider2D* collider1, Components::Collider2D* collider2);
		bool checkCollisionContinuous(Core::Entity* entityA, Core::Entity* entityB, Components::Collider2D* colliderA, Components::Collider2D* colliderB);
	};

}
}
