#pragma once
#include "BaseSystem.h"
#include "../Components/Collider2D.h"
#include "RavenStd/LinearAlgebra/Matrix.h"

namespace Raven {namespace Components {
	struct Transform;
}}

namespace Raven { namespace System {

	class RAVEN_API CollisionSystem2D : public BaseSystem {
	public:
		CollisionSystem2D();

		void Update(float dt) override;

	private:
		bool checkCollision(Core::Entity* element1, Core::Entity* element2, Components::Collider2D* collider1, Components::Collider2D* collider2);
		void UpdateTimes(float center, float bLeft, float bRight, float distance, float& tOpen, float& tClose, bool& separated);
		bool checkCollisionContinuous(Core::Entity* entityA, Core::Entity* entityB, Components::Collider2D* colliderA, Components::Collider2D* colliderB, float delta);
		RavenStd::Matrix& GetMatA2B(Components::Transform* transformA, Components::Transform* transformB);
	};

}
}
