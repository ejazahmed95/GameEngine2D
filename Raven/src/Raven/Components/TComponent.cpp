#include "TComponent.h"

namespace Raven { namespace Components {
	Types::t_id ComponentId::s_id = 0;
	Types::t_id ComponentId::Get() {
		s_id++;
		return s_id;
	}
}}
