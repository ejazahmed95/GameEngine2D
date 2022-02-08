#pragma once
#include "../Core.h"
#include "../CoreModule/Types.h"

namespace Raven { namespace Components {
	struct ComponentId {
		static Types::t_id s_id;
		static Types::t_id Get();
	};

	template <typename T>
	class RAVEN_API TComponent {
		static Types::t_id Id() {
			static Types::t_id s_id = ComponentId::Get();
			return s_id;
		}
	};
}}

