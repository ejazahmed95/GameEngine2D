#pragma once

#include "../Core.h"

namespace Raven { namespace System {

	class RAVEN_API BaseSystem {
	public:
		BaseSystem();
		virtual ~BaseSystem();

		virtual void Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Destroy() = 0;
	private:

	};
}}
