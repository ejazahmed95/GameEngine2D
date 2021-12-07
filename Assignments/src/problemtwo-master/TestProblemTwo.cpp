#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "Human.h"
#include "../InheritanceProbs.h"

// utility function that 
inline int RandInRange(int i_lowerBound, int i_upperBound) {
	assert(i_lowerBound < i_upperBound);

	return i_lowerBound + rand() % (i_upperBound - i_lowerBound);
}

void TestProblemTwo() {
	using namespace InheritanceTwo;

	std::cout << "=========================" << std::endl;
	std::cout << "Testing Problem Two" << std::endl;

	std::vector<Human>	AllHumans;
	
	// Human
	static const char* HumanNames[] = { "Larry", "Moe", "Curly", "Steve", "Joe", "Bob", "Henry", "Lyle", "John", "Kyle" };
	static const size_t numHumanNames = sizeof(HumanNames) / sizeof(HumanNames[0]);
	
	static unsigned int HumanNameUseCount[numHumanNames] = { 0 };
	
	unsigned int NameToUse = RandInRange(0, numHumanNames);
	
	char Temp[32];
	sprintf_s(Temp, sizeof(Temp), "%s %d", HumanNames[NameToUse], HumanNameUseCount[NameToUse]++);
	
	AllHumans.push_back(Human(Temp, Engine::Math::Vector2(static_cast<float>(RandInRange(-100, 100)), static_cast<float>(RandInRange(-100, 100))), 100));
	
	//std::random_shuffle(AllHumans.begin(), AllHumans.end());
	
	AllHumans.clear();
	
	std::cout << "=========== ** END ** ==============" << std::endl;

}
