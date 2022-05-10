#pragma once
#include "Raven/Components/SpriteRenderer.h"
#include "Raven/Systems/BaseSystem.h"

namespace Systems {
	class EnemySystem: public Raven::System::BaseSystem {
	public:
		EnemySystem();
		void Update(float dt) override;
	private:
		Raven::Core::Entity* playerRef;
	};
}
