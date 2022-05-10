#include "Editor.h"
#include <fstream>

#include "../ECSManager.h"
#include "RavenStd/Logger.h"
#include "../nlohmann/json.hpp"
#include "../Components/Transform.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/Collider2D.h"
#include "../Components/EnemyComponent.h"

#include "JobSystem/JobSystem.h"

using json = nlohmann::json;

namespace Raven { namespace Editor {
	void CreateGameObject(json gameObjectJson);
	void AddComponentsToEntity(Core::Entity* entity, json componentObj);
	void LoadConfig() {
		// TODO: Load the configuration file using a JSON
	}

	void LoadGameObjectsFromFile(const std::string fileName) {
		RavenStd::Log::I("Loading game objects from file..");

		// Load File into JSON Object
		std::ifstream input(fileName);
		if (!input) {
			RavenStd::Log::E("Unable to read file; File does not exist " + fileName);
			return;
		}
		json gameObjects;
		input >> gameObjects;
		input.close();

		//RavenStd::Log::D(to_string(gameObjects));
		if(!gameObjects.is_array()) {
			RavenStd::Log::E("JSON File must be an array");
			return;
		}

		Engine::JobSystem::JobStatus JobStatus;
		size_t entityCount = gameObjects.size();
		Engine::JobSystem::RunJob(
			Engine::JobSystem::GetDefaultQueueName(),
			[gameObjects]() {

				for (auto& go : gameObjects) {
					CreateGameObject(go);
				}
			},
			&JobStatus);
		JobStatus.WaitForZeroJobsLeft();

		RavenStd::Log::I("Finished loading entities. Total Entities = " + std::to_string(entityCount));
	}

	void LoadAssetsFromFile(const std::string fileName) {
		RavenStd::Log::I("Loading assets from file..");

		// Load File into JSON Object
		std::ifstream input(fileName);
		if (!input) {
			RavenStd::Log::E("Unable to read file; File does not exist " + fileName);
			return;
		}
		json assets;
		input >> assets;
		input.close();

		//RavenStd::Log::D(to_string(gameObjects));
		if (assets.contains("Textures")) {
			GetRenderer().AcquireOwnership()->LoadTextures(assets.at("Textures"));
			// RavenStd::Log::E("JSON File must be an array");
			return;
		}

		// Engine::JobSystem::JobStatus JobStatus;
		// size_t entityCount = gameObjects.size();
		// Engine::JobSystem::RunJob(
		// 	Engine::JobSystem::GetDefaultQueueName(),
		// 	[gameObjects]() {
		//
		// 		for (auto& go : gameObjects) {
		// 			CreateGameObject(go);
		// 		}
		// 	},
		// 	&JobStatus);
		// JobStatus.WaitForZeroJobsLeft();

		// RavenStd::Log::I("Finished loading entities. Total Entities = " + std::to_string(entityCount));
	}

	void CreateGameObject(json gameObjectJson) {
		RavenStd::Log::I("Creating a game object");
		auto entity = ECSManager::CreateEntity();
		if (gameObjectJson.contains("name")) {
			std::string name;
			gameObjectJson.at("name").get_to(name);
			entity->SetName(name);
		}
		AddComponentsToEntity(entity, gameObjectJson["components"]);
		AddGameplayComponentsToEntity(entity, gameObjectJson["components"]);
	}

	void AddComponentsToEntity(Core::Entity* entity, json componentObj) {
		if (!componentObj.is_object()) return;

		if (componentObj.contains("transform")) {
			auto transform = new Components::Transform();
			Components::Transform::from_json(componentObj.at("transform"), *transform);
			entity->AddComponent(transform);
		}

		if (componentObj.contains("sprite_renderer")) {
			std::string spriteRef = " ";
			auto renderer = new Components::SpriteRenderer(spriteRef);
			Components::SpriteRenderer::from_json(componentObj.at("sprite_renderer"), *renderer);
			entity->AddComponent(renderer);
		}

		if (componentObj.contains("physics")) {
			auto phyComp = new Components::PhysicsComponent();
			Components::PhysicsComponent::from_json(componentObj.at("physics"), *phyComp);
			entity->AddComponent(phyComp);
		}

		if (componentObj.contains("collision")) {
			auto collisionComp = new Components::Collider2D();
			Components::Collider2D::from_json(componentObj.at("collision"), *collisionComp);
			entity->AddComponent(collisionComp);
		}

		if(componentObj.contains("enemy")) {
			auto enemyComp = new Components::EnemyComponent();
			entity->AddComponent(enemyComp);
		}
	}
}}


