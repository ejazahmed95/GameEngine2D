#include "PhysicsSystem.h"
#include "../Components/Transform.h"
#include "../Components/PhysicsComponent.h"
#include "../CoreModule/Entity.h"

namespace Raven { namespace System {

	PhysicsSystem::PhysicsSystem() {
		using namespace Components;
		m_Mask.Add(Transform::Id());
		m_Mask.Add(PhysicsComponent::Id());
	}

	void PhysicsSystem::Update(float dt) {
		for (const auto& element : m_RegisteredEntities) {
			const auto physics = element->GetComponent<Components::PhysicsComponent>();
			const auto transform = element->GetComponent<Components::Transform>();

			auto dragForce = physics->vel.Mag() * physics->vel * physics->coefficientOfFriction * -1.0f;
			// Physics Velocity Update using verlet method
			physics->acc = (physics->force + dragForce)/ physics->mass;

			// TODO: Check for terminal velocity
			if((physics->acc*dt).Mag() > physics->vel.Mag() && physics->force == 0) {
				physics->vel = { 0,0,0 };
				continue;
			}

			Core::Point3D tempVel(0);
			tempVel = physics->vel + physics->acc * (dt / 2);
			SLib::Log::D(tempVel.toString());
			transform->position += tempVel * dt;
			physics->vel = tempVel + (physics->acc * (dt / 2));
		}
	}

}
}
