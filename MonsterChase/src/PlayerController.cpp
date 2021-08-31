#include "PlayerController.h"
#include <iostream>
#include <conio.h>

InputAction PlayerController::GetInputAction()
{
	InputAction action = InputAction::UNKNOWN;
	switch (_getch()) {
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
