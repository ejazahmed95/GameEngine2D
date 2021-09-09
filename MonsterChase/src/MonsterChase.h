#pragma once
#include "Raven.h"
#include "PlayerController.h"
#include "MonsterController.h"

class MonsterChase: public Raven::Application
{
public:
	MonsterChase(): pc_(nullptr), mc_(nullptr) {}
	~MonsterChase() override;
	void updateAllObjects();
	void startGame();
	void Run();

	// Removing copy constructors
	MonsterChase& operator=(const MonsterChase& m) = delete;
private:
	PlayerController* pc_;
	MonsterController* mc_;
};