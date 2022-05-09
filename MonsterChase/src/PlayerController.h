#pragma once
#include <string>
#include "Raven/CoreModule/CoreModule.h"

enum class InputAction {
	LEFT, RIGHT, UP, DOWN, QUIT, UNKNOWN
};

class PlayerController {
public:
	void Init();
};