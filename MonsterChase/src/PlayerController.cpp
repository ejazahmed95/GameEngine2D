#include "PlayerController.h"
#include <iostream>
#include <conio.h>

InputAction PlayerController::getInputAction(char in)
{
	InputAction action = InputAction::UNKNOWN;
	switch (in) {
	case 'w':	
	case 'W':
		action = InputAction::UP;
		break;
	case 'a':	
	case 'A':
		action = InputAction::LEFT;
		break;
	case 's':	
	case 'S':
		action = InputAction::DOWN;
		break;
	case 'd':	
	case 'D':
		action = InputAction::RIGHT;
		break;
	case 'q':	
	case 'Q':
		action = InputAction::QUIT;
		break;
	};
	return action;
}

void PlayerController::handleInput(char in)
{
	InputAction action = getInputAction(in);
	switch (action) {
	case InputAction::LEFT:
		setVelocity(-1, 0);
		break;
	case InputAction::RIGHT: 
		setVelocity(1, 0);
		break;
	case InputAction::UP: 
		setVelocity(0, 1);
		break;
	case InputAction::DOWN: 
		setVelocity(0, -1);
		break;
	case InputAction::QUIT: break;
	case InputAction::UNKNOWN: break;
	default: ;
	}
}

std::ostream& operator<<(std::ostream& lhs, const PlayerController& pc)
{
	lhs << pc.player_name_ << "=> Pos = " << pc.position().toString() << ", Vel = " << pc.velocity().toString();
	return lhs;
}
