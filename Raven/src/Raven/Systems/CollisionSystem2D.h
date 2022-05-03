#pragma once
#include "BaseSystem.h"
#include "../Components/Collider2D.h"
#include "../Components/Transform.h"

namespace Raven { namespace System {

	class RAVEN_API CollisionSystem2D : public BaseSystem {
	public:
		CollisionSystem2D();

		void Update(float dt) override;

	private:
		bool checkCollision(Components::Collider2D* collider1, Components::Transform* transform1, Components::Collider2D* collider2, Components::Transform* transform2);
	};

}
}
