#pragma once
#include <string>
#include "Raven/CoreModule/CoreModule.h"

enum class InputAction {
	LEFT, RIGHT, UP, DOWN, QUIT, UNKNOWN
};

class PlayerController : public Raven::GameObject
{
public:
	PlayerController(char* name): player_name_(name) {}

	~PlayerController() override
	{
		delete[] player_name_;
	}
	InputAction getInputAction(char in);
	void handleInput(char in);

	// Overrides
	// void update(float delta) override;

	friend std::ostream& operator<<(std::ostream& lhs, const PlayerController& pc);
private:
	char* player_name_;
};

