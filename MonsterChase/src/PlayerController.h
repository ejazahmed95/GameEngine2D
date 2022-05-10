#pragma once
#include <string>

#include "Attack.h"
#include "Raven/CoreModule/CoreModule.h"
#include "Raven/CoreModule/Entity.h"

enum class InputAction {
	LEFT, RIGHT, UP, DOWN, QUIT, UNKNOWN
};

class PlayerController {
public:
	void Init();
	void AddAttack();
private:
	Raven::Core::Entity* m_Entity;
	// std::vector<Attack*> m_Attacks;
};