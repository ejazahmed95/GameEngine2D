#pragma once
#include "Raven/Components/TComponent.h"
#include "Raven/nlohmann/json.hpp"

using json = nlohmann::json;

namespace Components {
	struct HealthComponent : Raven::Components::TComponent<HealthComponent> {
		float health = 1;
		static void from_json(const json& j, HealthComponent& comp) {
			j.at("health").get_to(comp.health);
		}

		void Damage(float d) {
			health -= d;
		}
	};
}
