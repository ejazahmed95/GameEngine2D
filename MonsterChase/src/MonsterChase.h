#pragma once
#include "Raven.h"
#include "PlayerController.h"
#include "Systems/EnemySystem.h"
#include "Systems/HealthSystem.h"

class MonsterChase: public Raven::Application
{
public:
	MonsterChase(): pc(nullptr) {
		m_HealthSystem = RavenStd::StrongPtr<Systems::HealthSystem>(new Systems::HealthSystem());
		m_EnemySystem = RavenStd::StrongPtr<Systems::EnemySystem>(new Systems::EnemySystem());
	}
	~MonsterChase() override;

	void GameStart() override;
	void GameEnd() override;
	void Update(float delta) override;

	// Removing copy constructors
	MonsterChase& operator=(const MonsterChase& m) = delete;
private:
	void CreateMonsters();
private:
	PlayerController* pc;
	RavenStd::StrongPtr<Systems::EnemySystem> m_EnemySystem;
	RavenStd::StrongPtr<Systems::HealthSystem> m_HealthSystem;
};
