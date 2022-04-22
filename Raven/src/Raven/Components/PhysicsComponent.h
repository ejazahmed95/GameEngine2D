#pragma once
#include "TComponent.h"
#include "../CoreModule/Point3D.h"

namespace Raven { namespace Components {

	struct RAVEN_API PhysicsComponent : TComponent<PhysicsComponent> {
		Core::Point3D vel = {0,0,0};
		Core::Point3D acc = {0,0,0};
		Core::Point3D force = {0,0,0};
		float mass = 1.0f;
		float coefficientOfFriction = 0.0f;
		void ApplyForce(const Core::Point3D& additionalForce) {
			force += additionalForce;
		}

		static void from_json(const json& j, PhysicsComponent& sr) {
			j.at("mass").get_to(sr.mass);
			j.at("e").get_to(sr.coefficientOfFriction);
			if(j.contains("velocity")) {
				Core::Point3D::from_json(j.at("velocity"), sr.vel);
			}
		}
	};
}
}
