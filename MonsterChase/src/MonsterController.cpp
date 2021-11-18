#include "MonsterController.h"

MonsterController::~MonsterController()
{
	// GameObject::~GameObject();
	for(int i=0;i<monster_count_;i++)
	{
		delete monsters_[i];
	}
	delete[] monsters_;
}

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
	total_monster_count_++;
}

void MonsterController::update(float delta)
{
	GameObject::update(delta);
	for(int i=0;i<monster_count_;i++) {
		auto m = monsters_[i];
		m->update(delta);
		if(m->age() > 5) {
			m->markForKill();
		}
	}

	// Adding monsters
	if(time_since_last_spawn_++ > spawn_interval_) {
		addMonster(getCustomName("nagini-", total_monster_count_));
		time_since_last_spawn_ = 0;
	}

	// Killing monsters
	for (int i = monster_count_-1; i >= 0; i--) {
		auto m = monsters_[i];
		if (m->age() > 5) {
			removeMonster(i);
		}
	}
}

void MonsterController::removeMonster(int index)
{
	Monster* temp = monsters_[index];
	monsters_[index] = monsters_[monster_count_ - 1];
	monster_count_--;
	delete temp;
	
}

char* MonsterController::getCustomName(const char* name, int index) const
{
	size_t len = strlen(name);
	auto s = std::to_string(index);
	const char* suffix = s.c_str();
	size_t newLength = strlen(name) + strlen(suffix) + 1;
	char* n = new char[newLength];
	memcpy(n, name, sizeof(char)*strlen(name));
	memcpy(n+len, suffix, sizeof(char)*strlen(suffix));
	std::cout << "Length = " << len << ";" << newLength << ";" << suffix << std::endl;
	n[newLength - 1] = '\0';
	return n;
}

void MonsterController::initialiseMonster(Monster* m) const
{
	int x = rand() % (spawn_range_ * 2) - spawn_range_;
	int y = rand() % (spawn_range_ * 2) - spawn_range_;
	int velx = rand() % 3;
	int vely = rand() % 3;
	m->setPosition(x, y);
	m->setVelocity(velx, vely);
}

std::ostream& operator<<(std::ostream& lhs, const MonsterController& mc)
{
	for(int i=0;i<mc.monster_count_;i++)
	{
		lhs << *mc.monsters_[i] << "\n";
	}
	return lhs;
}
