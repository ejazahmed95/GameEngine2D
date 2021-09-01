#pragma once
#include "PlayerController.h"
#include "MonsterController.h"

class MCGameManager
{
private:
	PlayerController pc;
	MonsterController mc;
	bool hasQuit;
public:
	MCGameManager(PlayerController pc, MonsterController mc) : pc(pc), mc(mc), hasQuit(false) {};
	void Play();
};

