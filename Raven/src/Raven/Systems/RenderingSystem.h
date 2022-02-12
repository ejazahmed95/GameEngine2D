#pragma once
#include "BaseSystem.h"

namespace Raven { namespace System {
	class RenderingSystem: public BaseSystem {
	public:
		void Initialize() override;
		void Update(float dt) override;
		void Destroy() override;
	private:

	};
}}
