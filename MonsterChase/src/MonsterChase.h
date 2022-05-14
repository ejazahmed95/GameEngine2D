#pragma once
#include "Raven.h"
#include "PlayerController.h"
#include "Systems/EnemySystem.h"
#include "Systems/HealthSystem.h"

class MonsterChase: public Raven::Application
{
public:
	MonsterChase();
	~MonsterChase() override;

	void GameStart() override;
	void Update(float delta) override;
	void GameEnd() override;

	// Removing copy constructors
	MonsterChase& operator=(const MonsterChase& m) = delete;
private:
	void EndGamePlay();

	PlayerController* pc;
	RavenStd::StrongPtr<Systems::EnemySystem> m_EnemySystem;
	RavenStd::StrongPtr<Systems::HealthSystem> m_HealthSystem;
	bool m_GameEnded = false;
};
