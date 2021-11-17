#pragma once

#include <iostream>

#include "GameActor.h"
#include "math/Vector2.h"

#include <string.h>
#include <stdlib.h>

// I am a GameActor that is a human being
class Human : public GameActor
{
public:
	Human(const char* i_pName, const Engine::Math::Vector2& i_InitialPosition, int i_InitialHealth) :
		GameActor(i_InitialPosition, i_InitialHealth),
		m_Name(_strdup(i_pName ? i_pName : "Unknown"))
	{ }
	~Human()
	{
		std::cout << "Human destroyed" << std::endl;
		if (m_Name)
			free(const_cast<char*>(m_Name));
	}

	Human(const Human& other) :
		GameActor(Engine::Math::Vector2(0, 0), 100),
		m_Name(_strdup(other.m_Name ? other.m_Name : "Unknown")) {
		std::cout << "Human:: const copy constructor!!" << std::endl;
	}

	// what's my name
	const char* getName() const { return m_Name; }

	// return my specific type
	virtual const char* getTypeName() const override { return "Human"; }
private:
	const char* m_Name;
};

