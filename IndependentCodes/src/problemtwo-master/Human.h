#pragma once

#include <iostream>

#include "GameActor.h"
#include "../math/Vector2.h"

#include <string.h>
#include <stdlib.h>

// I am a GameActor that is a human being
namespace InheritanceTwo {
	class Human : public GameActor {
	public:
		Human(const char* i_pName, const Engine::Math::Vector2& i_InitialPosition, int i_InitialHealth) :
			GameActor(i_InitialPosition, i_InitialHealth),
			m_Name(_strdup(i_pName ? i_pName : "Unknown")) {
			std::cout << "Human getting created!!" << std::endl;
		}

		~Human() {
			std::cout << "Human getting destroyed!!" << std::endl;
			if (m_Name)
				free(const_cast<char*>(m_Name));
		}
		//
		// Human(): GameActor(Engine::Math::Vector2(0,0), 100) {
		// 	std::cout << "Human:: default constructor!!" << std::endl;
		// }

		Human(const Human& other) :
			GameActor(Engine::Math::Vector2(0, 0), 100),
			m_Name(_strdup(other.m_Name ? other.m_Name: "Unknown")) {
			std::cout << "Human:: const copy constructor!!" << std::endl;
		}

		Human& operator=(const Human& other) {
			delete[] m_Name;

			m_Name = _strdup(other.m_Name ? other.m_Name : "Unknown");
			return *this;
		}

		// what's my name
		const char* getName() const { return m_Name; }

		// return my specific type
		const char* getTypeName() const override { return "Human"; }
	private:
		const char* m_Name;
	};
}
