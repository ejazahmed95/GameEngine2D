#pragma once
#include "TComponent.h"
#include "../CoreModule/Point3D.h"
#include "../Core.h"
#include "../nlohmann/json.hpp"

namespace Raven { namespace Components {
	struct RAVEN_API Transform: public TComponent<Transform> {
		Core::Point3D position;
		Core::Point3D rotation;

		Transform() : position(0), rotation(0) {}
		void Translate(Core::Point3D);
		void Rotate(Core::Point3D);

		static void from_json(const json& j, Components::Transform& t) {
			Core::Point3D::from_json(j.at("position"), t.position);
			Core::Point3D::from_json(j.at("rotation"), t.rotation);
		}
	};
	
}}
