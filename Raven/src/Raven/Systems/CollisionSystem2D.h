#pragma once
#include "BaseSystem.h"
#include "../Components/Collider2D.h"
#include "../Components/Transform.h"
#include "RavenStd/LinearAlgebra/Matrix.h"


namespace Raven { namespace System {

	class RAVEN_API CollisionSystem2D : public BaseSystem {
	public:
		CollisionSystem2D();

		void Update(float dt) override;
		
	private:
		bool checkCollision(Core::Entity* elementA, Core::Entity* elementB, Components::Collider2D* colliderA, Components::Collider2D* colliderB) const;
		void updateTimes(float center, float bLeft, float bRight, float distance, float& tOpen, float& tClose, bool& separated);
		bool checkCollisionContinuous(Core::Entity* entityA, Core::Entity* entityB, Components::Collider2D* colliderA, Components::Collider2D* colliderB, float dt);
		RavenStd::Matrix getMatA2B(Components::Transform* transformA, Components::Transform* transformB);
	};

}
}
