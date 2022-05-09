#include "PlayerController.h"

#include "Raven/ECSManager.h"
#include "Raven/Systems.h"
#include "Raven/Components/Collider2D.h"
#include "Raven/Components/InputComponent.h"
#include "Raven/Components/PhysicsComponent.h"

void PlayerController::Init() {
	using namespace Raven::Components;

	auto pikachu = Raven::GetECS().AcquireOwnership()->GetEntityByName("Pikachu");
	auto physics = pikachu->GetComponent<PhysicsComponent>();
	auto collider = pikachu->GetComponent<Collider2D>();

	collider->SetCallback([](Raven::Core::Entity* entity) {
		RavenStd::Log::I("Player Is Colliding with:: " + entity->GetName());
		});

	pikachu->AddComponent(new InputComponent([physics](unsigned keyID, bool pressed) {
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
		}
		}));
}
