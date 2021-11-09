#pragma once

#include "GameActor.h"
#include "math/Vector2.h"


// This is a GameActor that's a monster
class Monster : public GameActor
{
public:
	Monster(const Engine::Math::Vector2& i_InitialPosition, int i_InitialHealth) :
		GameActor(i_InitialPosition, i_InitialHealth)
	{ }

	// return my specific type
	virtual const char* getTypeName() const override { return "Monster"; }
};