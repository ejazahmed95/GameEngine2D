#include "Raven/Editor/Editor.h"
#include "Components/EnemyAIComp.h"
#include "Components/HealthComponent.h"
#include "Raven/CoreModule/Entity.h"

void Raven::Editor::AddGameplayComponentsToEntity(Core::Entity* entity, json componentObj) {
	if (!componentObj.is_object()) return;

	if (componentObj.contains("EnemyAI")) {
		auto enemyComp = new ::Components::EnemyAIComp();
		::Components::EnemyAIComp::from_json(componentObj.at("EnemyAI"), *enemyComp);
		entity->AddComponent(enemyComp);
	}

	if(componentObj.contains("health")) {
		auto healthComp = new ::Components::HealthComponent();
		::Components::HealthComponent::from_json(componentObj.at("health"), *healthComp);
		entity->AddComponent(healthComp);
	}
}
