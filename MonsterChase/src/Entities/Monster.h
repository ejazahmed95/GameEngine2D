#pragma once
#include "Raven/CoreModule/CoreModule.h"
#include<iostream>

class Monster : public Raven::GameObject
{
public:
	Monster(std::string name) : monster_name_(name), is_dead_(false), age_(0) {}
	~Monster() override;
	friend std::ostream& operator<<(std::ostream& lhs, const Monster& m);

	// Getters and setters
	bool isDead() const { return is_dead_;}
	int age() const { return age_; }

	void markForKill();

	// Overrides
	void update(float delta) override;
private:
	std::string monster_name_;
	bool is_dead_;
	int age_;
};