// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

MonsterChase::MonsterChase(): pc(nullptr) {
	m_HealthSystem = RavenStd::StrongPtr<Systems::HealthSystem>(new Systems::HealthSystem());
	m_EnemySystem = RavenStd::StrongPtr<Systems::EnemySystem>(new Systems::EnemySystem());
}

MonsterChase::~MonsterChase() {
	delete pc;
};

void MonsterChase::GameStart() {
	Application::GameStart();

	srand(static_cast<int>(time(nullptr)));
	pc = new PlayerController();
	pc->Init();
}

void MonsterChase::Update(float delta) {
	Application::Update(delta);

	if (m_GameEnded) return;
	if(m_HealthSystem->GetEnemyDeadCount() >= 4 || m_HealthSystem->GetPlayerDeadCount() >= 1) {
		// You Win
		auto entity = Raven::ECSManager::CreateEntity();
		std::string texName = (m_HealthSystem->GetEnemyDeadCount() >= 4)? "win": "game-over";
		auto renderer = new Raven::Components::SpriteRenderer(texName);
		auto transform = new Raven::Components::Transform();
		transform->Translate({ 0, -256, 0 });
		entity->AddComponent(transform);
		entity->AddComponent(renderer);
		EndGamePlay();
	}

}

void MonsterChase::EndGamePlay() {
	Raven::GetECS().AcquireOwnership()->GetEntityByName("Pikachu")->Destroy();
	Raven::GetRenderer().AcquireOwnership()->SetBgColor();
	m_GameEnded = true;
}

void MonsterChase::GameEnd() {
	Application::GameEnd();
}
