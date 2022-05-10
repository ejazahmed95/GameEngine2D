#pragma once
#include "Raven/Systems/BaseSystem.h"

namespace Systems {
	class HealthSystem : public Raven::System::BaseSystem {
	public:
		HealthSystem();
		void Update(float dt) override;
	};
}
