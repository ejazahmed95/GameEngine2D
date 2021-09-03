#pragma once
#include "Raven.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include<iostream>

class MonsterChase: public Raven::Application
{
public:
	MonsterChase(): pc_(nullptr), mc_(nullptr) {}
	void updateAllObjects();
	void startGame();
	void Run();
private:
	MonsterController* mc_;
	PlayerController* pc_;
};