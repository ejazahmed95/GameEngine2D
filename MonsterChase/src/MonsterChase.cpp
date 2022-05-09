// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

#include "Raven/Components/Collider2D.h"
#include "Raven/Components/InputComponent.h"
#include "Raven/Components/PhysicsComponent.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::~MonsterChase() {
	delete pc;
};

void MonsterChase::GameStart() {
	Application::GameStart();
	
	// Raven::GetRenderer().AcquireOwnership()->LoadSprites(sprites);

	// srand(static_cast<int>(time(nullptr)));
	pc = new PlayerController();
	pc->Init();
	
}

void MonsterChase::Update(float delta) {
	Application::Update(delta);



}

void MonsterChase::GameEnd() {
	Application::GameEnd();
	// GLib::Release(playerSprite);
}
