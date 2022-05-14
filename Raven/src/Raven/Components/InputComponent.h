#pragma once
#include <functional>
#include "TComponent.h"

namespace Raven { namespace Components {
	struct RAVEN_API InputComponent : public TComponent<InputComponent> {
		std::function<void(unsigned i_VKeyID, bool i_bDown)> OnInputChange;

		InputComponent(const std::function<void(unsigned i_VKeyID, bool i_bDown)>& func): OnInputChange(func){}
	};
}
}
