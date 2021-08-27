#include "MCGameManager.h"
#include <iostream>

void MCGameManager::Play() {
	std::cout << "Start Playing!" << std::endl;
	while (!hasQuit) {
		InputAction action = pc.GetInputAction();
		switch (action)
		{
		case InputAction::LEFT:
			std::cout << "Player Moving Left" << std::endl;
			break;
		case InputAction::RIGHT:
			std::cout << "Player Moving Right" << std::endl;
			break;
		case InputAction::UP:
			std::cout << "Player Moving Up" << std::endl;
			break;
		case InputAction::DOWN:
			std::cout << "Player Moving Down" << std::endl;
			break;
		case InputAction::QUIT:
			std::cout << "Player Going to Quit" << std::endl;
			hasQuit = true;
			break;
		default:
			std::cout << "Unrevognised input" << std::endl;
			break;
		}
	}
}