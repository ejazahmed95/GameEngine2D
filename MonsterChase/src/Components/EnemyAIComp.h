#pragma once

#include "Raven/Components/TComponent.h"
#include "Raven/nlohmann/json.hpp"

using json = nlohmann::json;

namespace Components {
	struct EnemyAIComp : Raven::Components::TComponent<EnemyAIComp> {
		float attackInterval = 3.0f;
		float timeElapsed = 0;

		static void from_json(const json& j, EnemyAIComp& comp) {
			if(j.contains("attackInterval")) j.at("attackInterval").get_to(comp.attackInterval);
		}
	};
}
