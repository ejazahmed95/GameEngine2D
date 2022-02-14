// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

#include <ctime>

#include "Raven/Components/InputComponent.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::~MonsterChase() = default;



void MonsterChase::GameStart() {
	Application::GameStart();
	std::vector<std::string> sprites;
	sprites.push_back("assets\\sprites\\pikachu.dds");
	sprites.push_back("assets\\sprites\\gastly.dds");
	Raven::GetRenderer()->LoadSprites(sprites);

	srand(time(NULL));
	using namespace Raven::Components;
	auto player = Raven::ECSManager::CreateEntity();
	player->AddComponent(new Transform());
	player->AddComponent(new SpriteRenderer(sprites[0]));
	auto transform = player->GetComponent<Transform>();
	
	player->AddComponent(new InputComponent([transform](unsigned keyID, bool pressed) {
		switch (keyID) {
		case 0x0057:
			transform->Translate({0, 30.0f, 0});
			break;
		case 0x0041:
			transform->Translate({ -30.0f, 0.0f, 0 });
			break;
		case 0x0053:
			transform->Translate({ 0, -30.0f, 0 });
			break;
		case 0x0044:
			transform->Translate({ 30.0f, 0.0f, 0 });
			break;
		}
		}));

	CreateMonsters();
}

void MonsterChase::CreateMonsters() {
	using namespace Raven::Components;
	
	for(int i=0;i<3;i++) {
		std::string monsterSprite = "assets\\sprites\\gastly.dds";
		auto entity = Raven::ECSManager::CreateEntity();
		auto transform = new Transform();
		transform->Translate({ rand() % 400 - 200.0f, rand() % 400 - 200.0f, 0 });
		entity->AddComponent(transform);
		entity->AddComponent(new SpriteRenderer(monsterSprite));
		entity->AddComponent(new InputComponent([transform](unsigned keyID, bool pressed) {
			switch (keyID) {
			case 0x0057:
				transform->Translate({ 0, -30.0f, 0 });
				break;
			case 0x0041:
				transform->Translate({ 30.0f, 0.0f, 0 });
				break;
			case 0x0053:
				transform->Translate({ 0, 30.0f, 0 });
				break;
			case 0x0044:
				transform->Translate({ -30.0f, 0.0f, 0 });
				break;
			}
			}));
	}
}

void MonsterChase::Update(float delta) {
	Application::Update(delta);
}

void MonsterChase::GameEnd() {
	// GLib::Release(playerSprite);
}
