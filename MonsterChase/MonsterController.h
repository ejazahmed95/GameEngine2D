#pragma once

class MonsterController
{
public:
	MonsterController(int initialMonsters) {};
};

/*
* Memory leak detection
* 
* _CrtDumpMemoryLeaks()
* _CrtSetBreakAlloc()
* These do not detect the memory leaks caused by global variables as they are not tracked. Their scope lies outside of main.
*/
