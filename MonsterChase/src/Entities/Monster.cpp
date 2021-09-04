#include "Monster.h"

std::ostream& operator<<(std::ostream& lhs, const Monster& m) {
	lhs << m.monster_name_ << "=> Pos = "<< m.position().toString() << ", Vel = " << m.velocity().toString() <<
		", Age = " << m.age_;
	return lhs;
}

Monster::~Monster()
{
	// GameObject::~GameObject();
	delete[] monster_name_;
}

void Monster::markForKill()
{
	is_dead_ = true;
}

void Monster::update(float delta)
{
	age_++;
	GameObject::update(delta);
}
