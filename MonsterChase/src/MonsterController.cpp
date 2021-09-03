#include "MonsterController.h"

#include <cstdint>
#include <cstring>
#include <iostream>

void MonsterController::addMonster(char* name)
{
	const auto m = new Monster(name);
	initialiseMonster(m);
	const auto temp = monsters_;
	monsters_ = new Monster * [static_cast<int64_t>(1) + monster_count_];
	memcpy(monsters_, temp, monster_count_ * sizeof(Monster*));
	monsters_[monster_count_] = m;
	if(monster_count_ > 0) delete[] temp;
	monster_count_++;
}

void MonsterController::update(float delta)
{

}

void MonsterController::initialiseMonster(Monster* m) const
{
	int x = rand() % (spawn_range_ * 2) - spawn_range_;
	int y = rand() % (spawn_range_ * 2) - spawn_range_;
	m->setPosition(x, y);
}

std::ostream& operator<<(std::ostream& lhs, const MonsterController& mc)
{
	for(int i=0;i<mc.monster_count_;i++)
	{
		lhs << *mc.monsters_[i] << "\n";
	}
	return lhs;
}
