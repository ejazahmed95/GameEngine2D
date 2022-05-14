#pragma once
#include "BaseSystem.h"

namespace Raven { namespace System {
	class InputSystem: public BaseSystem {
	public:
		InputSystem();

		void Initialize() override;
		void Update(float dt) override;
		void Destroy() override;

		void OnInChange(unsigned i_VKeyID, bool bWentDown) const;
	private:
	};
	void OnInputChange(unsigned int i_VKeyID, bool bWentDown);
}}

