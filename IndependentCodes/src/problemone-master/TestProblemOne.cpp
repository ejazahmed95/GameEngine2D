#include <iostream>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <crtdbg.h>

#include <vector>

#include "../math/Vector2.h"
#include "GameActor.h"
#include "Human.h"
#include "Monster.h"
#include "Game.h"

#include "../InheritanceProbs.h"

// Only exported function
void TestProblemOne() {
	std::cout << "========================" << std::endl;
	std::cout << "Testing Problem One" << std::endl;
	RunGame();
	std::cout << "========================" << std::endl;
}

// utility function that 
inline int RandInRange(int i_lowerBound, int i_upperBound) {
	assert(i_lowerBound < i_upperBound);

	return i_lowerBound + rand() % (i_upperBound - i_lowerBound);
}

void RunGame() {
	std::vector<GameActor*>	AllActors;

	const size_t numActors = 100;

	// set up 100 random GameActors
	for (size_t i = 0; i < numActors; i++) {
		// 50% chance to create a Monster, 50% chance to create a Human. Make it fair
		if (rand() & 1) {
			// Monster
			AllActors.push_back(new Monster(Engine::Math::Vector2(static_cast<float>(RandInRange(-100, 100)), static_cast<float>(RandInRange(-100, 100))), 100));
		} else {
			// Human
			static const char* HumanNames[] = { "Larry", "Moe", "Curly", "Steve", "Joe", "Bob", "Henry", "Lyle", "John", "Kyle" };
			static const size_t numHumanNames = sizeof(HumanNames) / sizeof(HumanNames[0]);

			static unsigned int HumanNameUseCount[numHumanNames] = { 0 };

			unsigned int NameToUse = RandInRange(0, numHumanNames);

			char Temp[32];
			sprintf_s(Temp, sizeof(Temp), "%s %d", HumanNames[NameToUse], HumanNameUseCount[NameToUse]++);

			AllActors.push_back(new Human(Temp, Engine::Math::Vector2(static_cast<float>(RandInRange(-100, 100)), static_cast<float>(RandInRange(-100, 100))), 100));
		}
	}

	// now go through them and randomly decrease health until only one survives
	while (1) {
		std::vector<GameActor*>::iterator iter = AllActors.begin();

		// update this GameActor's Health
		(*iter)->UpdateHealth(RandInRange(-10, 0));
		// if it's below zero they're out
		if ((*iter)->GetHealth() < 0) {
			// delete them
			delete (*iter);
			// erase them from the vector
			iter = AllActors.erase(iter);

			// if there's only one left, determine if it was a Monster or Human
			if (AllActors.size() == 1) {
				const char* pTypeName = (*iter)->getTypeName();
				printf("The last GameActor standing is a %s. %s types win!!!!\n", pTypeName, pTypeName);
				break;
			}
		}
	}
	for (const auto& actor : AllActors) {
		delete actor;
	}
	AllActors.clear();
}
