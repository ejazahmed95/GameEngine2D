#pragma once
#include "Raven/CoreModule/Entity.h"
#include "Raven/CoreModule/Point3D.h"

class Attack {
public:
	Attack(Raven::Core::Point3D pos, Raven::Core::Point3D dir, bool isPlayer);
private:
	Raven::Core::Entity* m_Entity;
	float m_Damage = 3.0f;
	bool m_IsPlayer;
};
