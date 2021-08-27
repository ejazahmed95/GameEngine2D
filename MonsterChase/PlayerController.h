#pragma once
#include <string>

enum class InputAction {
	LEFT, RIGHT, UP, DOWN, QUIT, UNKNOWN
};
class PlayerController
{
private:
	std::string playerName;
public:
	PlayerController(std::string playerName) : playerName(playerName) {};
	InputAction GetInputAction();
};

