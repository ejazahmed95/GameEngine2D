#pragma once

#include "BaseSystem.h"
#include "../Core.h"

namespace Raven { namespace System {
	class RAVEN_API PhysicsSystem: public BaseSystem {
	public:
		PhysicsSystem();

		void Update(float dt) override;
	};
}
}
