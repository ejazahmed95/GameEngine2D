#include "PlayerController.h"

#include "Raven/ECSManager.h"
#include "Raven/Systems.h"
#include "Raven/Components/Collider2D.h"
#include "Raven/Components/InputComponent.h"
#include "Raven/Components/PhysicsComponent.h"
#include "Raven/Components/Transform.h"

void PlayerController::Init() {
	using namespace Raven::Components;

	m_Entity = Raven::GetECS().AcquireOwnership()->GetEntityByName("Pikachu");
	auto physics = m_Entity->GetComponent<PhysicsComponent>();
	auto collider = m_Entity->GetComponent<Collider2D>();
	auto transform = m_Entity->GetComponent<Transform>();
	auto attackSpawner = m_Entity->GetComponent<Collider2D>();

	collider->SetCallback([](Raven::Core::Entity* entity) {
		RavenStd::Log::I("Player Is Colliding with:: " + entity->GetName());
		});

	m_Entity->AddComponent(new InputComponent([physics, transform, this](unsigned keyID, bool pressed) {
		float factor = pressed ? 1.0f : -1.0f;
		float forceFactor = 500;
		switch (keyID) {
		case 0x0057: // W
			physics->ApplyForce(Raven::Core::Point3D(0, forceFactor, 0) * factor);
			break;
		case 0x0041: // A
			physics->ApplyForce(Raven::Core::Point3D(-forceFactor, 0.0f, 0) * factor);
			break;
		case 0x0053: // S
			physics->ApplyForce(Raven::Core::Point3D(0, -forceFactor, 0) * factor);
			break;
		case 0x0044: // D
			physics->ApplyForce(Raven::Core::Point3D(forceFactor, 0.0f, 0) * factor);
			break;
		case 0x0045: // E
			if(pressed) transform->Rotate(Raven::Core::Point3D(0, 0, 0.5));
			break;
		case 0x0052: // R
			if(pressed) transform->Rotate(Raven::Core::Point3D(0, 0, -0.5));
			break;
		case 0x0020: // Space
			if(pressed) {
				AddAttack();
			}
		}
		}));
}

void PlayerController::AddAttack() {
	auto transform = m_Entity->GetComponent<Raven::Components::Transform>();
	auto pos = transform->Object2WorldMatrix() * Raven::Core::Point3D(0, 50, 0).ToVec4(1);
	auto rot = transform->Object2WorldMatrix() * Raven::Core::Point3D(0, 1, 0).ToVec4();
	auto attack = RavenStd::StrongPtr<Attack>(new Attack({pos.X(), pos.Y(), pos.Z()}, { rot.X(), rot.Y(), rot.Z() }, true));
}