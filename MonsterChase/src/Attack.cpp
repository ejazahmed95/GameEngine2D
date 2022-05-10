#include "Attack.h"

#include "Components/HealthComponent.h"
#include "Raven/ECSManager.h"
#include "Raven/Systems.h"
#include "Raven/Components/Collider2D.h"
#include "Raven/Components/PhysicsComponent.h"
#include "Raven/Components/Transform.h"
#include "Raven/Components/SpriteRenderer.h"

Attack::Attack(Raven::Core::Point3D pos, Raven::Core::Point3D dir, bool isPlayer) {
	using namespace Raven::Components;

	m_Entity = Raven::GetECS().AcquireOwnership()->CreateEntity();
	m_IsPlayer = isPlayer;
	m_Entity->SetTag((isPlayer) ? "Player" : "Enemy");
	std::string texName = isPlayer? "elec-04": "shadow-04";
	m_Damage = isPlayer? 3.0f: 1.0f;

	auto transform = new Transform();
	transform->position = pos;

	auto renderComp = new SpriteRenderer(texName);
	renderComp->scale = Raven::Core::Point3D(0.25);

	auto physicsComp = new PhysicsComponent();
	physicsComp->vel = dir * (200/dir.Mag());
	
	auto collisionComp = new Collider2D();
	collisionComp->bounds = AABB();
	collisionComp->bounds.center = Raven::Core::Point3D(0, 20, 0);
	collisionComp->bounds.extents = Raven::Core::Point3D(20, 20, 0);
	auto entityRef = m_Entity;
	collisionComp->SetCallback([isPlayer, entityRef](Raven::Core::Entity* entity) {
		auto healthComp = entity->GetComponent<Components::HealthComponent>();
		if (healthComp == nullptr) return;
		// Todo: Collision layer should ignore the collision
		healthComp->Damage(3);
		entityRef->Destroy();
		});

	m_Entity->AddComponent(transform);
	m_Entity->AddComponent(renderComp);
	m_Entity->AddComponent(physicsComp);
	m_Entity->AddComponent(collisionComp);
}
