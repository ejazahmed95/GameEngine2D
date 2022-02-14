// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

#include "Raven/Components/InputComponent.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::~MonsterChase() = default;



void MonsterChase::GameStart() {
	Application::GameStart();
	std::vector<std::string> sprites;
	sprites.push_back("assets\\sprites\\gastly.dds");
	Raven::GetRenderer()->LoadSprites(sprites);

	using namespace Raven::Components;
	auto player = Raven::ECSManager::CreateEntity();
	player->AddComponent(new Transform());
	player->AddComponent(new SpriteRenderer(sprites[0]));
	auto transform = player->GetComponent<Transform>();
	// bool a = false;
	// unsigned b = 0;
	// auto inputComp = new InputComponent();
	// inputComp->OnInputChange = [b](bool) {
	//
	// };

	
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

}

void MonsterChase::Update(float delta) {
	// Application::Update(delta);
	// bool quit = false;
	// GLib::Service(quit);
	// GLib::BeginRendering(DirectX::Colors::Aqua);
	// drawAllObjects();
	// GLib::EndRendering();
}

void MonsterChase::GameEnd() {
	// GLib::Release(playerSprite);
}
