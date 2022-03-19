// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

#include <ctime>

#include "Raven/Components/InputComponent.h"
#include "Raven/Components/PhysicsComponent.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::~MonsterChase() = default;

void MonsterChase::GameStart() {
	Application::GameStart();
	std::vector<std::string> sprites;

	// TODO: Add list of sprites in JSON
	sprites.push_back("assets\\sprites\\pikachu.dds");
	sprites.push_back("assets\\sprites\\gastly.dds");
	Raven::GetRenderer().AcquireOwnership()->LoadSprites(sprites);

	srand(static_cast<int>(time(nullptr)));
	using namespace Raven::Components;
	auto player = Raven::ECSManager::CreateEntity();
	player->AddComponent(new Transform());
	player->AddComponent(new SpriteRenderer(sprites[0]));
	player->AddComponent(new PhysicsComponent());
	auto physics = player->GetComponent<PhysicsComponent>();
	physics->coefficientOfFriction = 0.005f;
	// physics->vel.SetX(10);
	
	player->AddComponent(new InputComponent([physics](unsigned keyID, bool pressed) {
		float factor = pressed ? 1.0f : -1.0f;
		float forceFactor = 500;
		switch (keyID) {
		case 0x0057:
			physics->ApplyForce(Raven::Core::Point3D(0, forceFactor, 0)*factor);
			break;
		case 0x0041:
			physics->ApplyForce(Raven::Core::Point3D( -forceFactor, 0.0f, 0 )*factor);
			break;
		case 0x0053:
			physics->ApplyForce(Raven::Core::Point3D( 0, -forceFactor, 0 )*factor);
			break;
		case 0x0044:
			physics->ApplyForce(Raven::Core::Point3D( forceFactor, 0.0f, 0 )*factor);
			break;
		}
		}));
}

void MonsterChase::Update(float delta) {
	Application::Update(delta);
}

void MonsterChase::GameEnd() {
	Application::GameEnd();
	// GLib::Release(playerSprite);
}
