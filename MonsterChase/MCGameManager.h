#pragma once
#include "PlayerController.h"
#include "MonsterController.h"

class MCGameManager
{
private:
	PlayerController pc;
	MonsterController mc;
	int gridSize;
	bool hasQuit;
public:
	MCGameManager(PlayerController pc, MonsterController mc, int gridSize) : pc(pc), mc(mc), gridSize(gridSize), hasQuit(false) {};
	void Play();
};

