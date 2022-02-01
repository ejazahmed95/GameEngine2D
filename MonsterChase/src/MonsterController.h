#pragma once
#include "Entities/Monster.h"

class MonsterController: Raven::GameObject
{
public:
	MonsterController(): monster_count_(0), spawn_range_(30), spawn_interval_(3), monsters_(nullptr) {
		time_since_last_spawn_ = 0;
		total_monster_count_ = 0;
	}
	~MonsterController() override;
	void addMonster(std::string name);
	void update(float delta) override;
	void draw();
	void removeMonster(int index);
	friend std::ostream& operator<<(std::ostream& lhs, const MonsterController& mc);
	std::string getCustomName(const char* name, int index) const;
private:
	int monster_count_, spawn_range_, spawn_interval_;
	int time_since_last_spawn_;
	int total_monster_count_;
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
