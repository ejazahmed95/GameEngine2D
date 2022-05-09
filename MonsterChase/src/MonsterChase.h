#pragma once
#include "Raven.h"
#include "PlayerController.h"

class MonsterChase: public Raven::Application
{
public:
	MonsterChase(): pc(nullptr) {}
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
};
