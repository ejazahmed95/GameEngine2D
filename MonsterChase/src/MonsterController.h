#pragma once
#include "Raven.h"
#include "Entities/Monster.h"

class MonsterController: Raven::GameObject
{
public:
	MonsterController(): monster_count_(0), spawn_range_(30), spawn_interval_(3), monsters_(nullptr)
	{

	}

	void addMonster(char* name);
	void update(float delta) override;
	friend std::ostream& operator<<(std::ostream& lhs, const MonsterController& mc);

private:
	int monster_count_, spawn_range_, spawn_interval_;
	void initialiseMonster(Monster* m) const;
	Monster** monsters_;
};

/*
* Memory leak detection
* 
* _CrtDumpMemoryLeaks()
* _CrtSetBreakAlloc()
* These do not detect the memory leaks caused by global variables as they are not tracked. Their scope lies outside of main.
*/
