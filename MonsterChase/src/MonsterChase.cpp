// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::~MonsterChase() = default;



void MonsterChase::GameStart() {
	Application::GameStart();
	std::vector<std::string> sprites;
	sprites.push_back("assets\\sprites\\gastly.dds");
	Raven::GetRenderer()->LoadSprites(sprites);

	auto player = Raven::ECSManager::CreateEntity();
	player->AddComponent(new Raven::Components::Transform());
	player->AddComponent(new Raven::Components::SpriteRenderer(sprites[0]));


	// int mCount = 1;
	// char playerName[] = "Ejaz";
	// this->mc_ = new MonsterController();
	// this->pc_ = new PlayerController(playerName);
	// for (int i = 0; i < mCount; i++) {
		//std::cout << "Enter the name of monster " << i << ": ";
		
	// }
	// startWinGame();
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
