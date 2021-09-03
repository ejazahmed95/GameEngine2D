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
		setVelocity(-1, 0);
		break;
	case InputAction::UP: 
		setVelocity(-1, 0);
		break;
	case InputAction::DOWN: 
		setVelocity(-1, 0);
		break;
	case InputAction::QUIT: break;
	case InputAction::UNKNOWN: break;
	default: ;
	}
}

std::ostream& operator<<(std::ostream& lhs, const PlayerController& pc)
{
	lhs << pc.name() << "=> Pos = " << pc.position() << ", Vel = " << pc.velocity();
	return lhs;
}
