#pragma once
#include "Raven/CoreModule/CoreModule.h"
#include<iostream>

class Monster: public Raven::GameObject
{
public:
	Monster(char* name): name_(name) {}

	friend std::ostream& operator<<(std::ostream& lhs, const Monster& m);

private:
	char* name_;
};
