#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <crtdbg.h>

#include <algorithm>
#include <vector>

#include "math/Vector2.h"
#include "GameActor.h"
#include "Human.h"

// utility function that 
inline int RandInRange(int i_lowerBound, int i_upperBound)
{
	assert(i_lowerBound < i_upperBound);

	return i_lowerBound + rand() % (i_upperBound - i_lowerBound);
}

int main(int i_argc, char** i_argl)
{
	{
		std::vector<Human>	AllHumans;

		// Human
		static const char* HumanNames[] = { "Larry", "Moe", "Curly", "Steve", "Joe", "Bob", "Henry", "Lyle", "John", "Kyle" };
		static const size_t numHumanNames = sizeof(HumanNames) / sizeof(HumanNames[0]);

		static unsigned int HumanNameUseCount[numHumanNames] = { 0 };

		unsigned int NameToUse = RandInRange(0, numHumanNames);

		char Temp[32];
		sprintf_s(Temp, sizeof(Temp), "%s %d", HumanNames[NameToUse], HumanNameUseCount[NameToUse]++);

		AllHumans.push_back(Human(Temp, Engine::Math::Vector2(static_cast<float>(RandInRange(-100, 100)), static_cast<float>(RandInRange(-100, 100))), 100));

		std::random_shuffle(AllHumans.begin(), AllHumans.end());

		AllHumans.clear();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}