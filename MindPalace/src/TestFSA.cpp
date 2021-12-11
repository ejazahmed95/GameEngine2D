#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "MemorySystem.h"
#include "TestHelpers.h"

void TestFSA() {
	using namespace std;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, 1024 * 10);
	assert(pHeapMemory);
	// Create your HeapManager and FixedSizeAllocators.
	auto hm = CreateHeapManager(pHeapMemory, 1024 * 10, 0);
	FSAInfo info(16, 100);
	std::vector<void*> v;
	v.reserve(100);
	info.startLoc = reinterpret_cast<uintptr_t>(hm->alloc(info.size * info.numBlocks));
	FixedSizeAllocator* allocator = new FixedSizeAllocator(info);
	void* ptr = nullptr;
	ptr = allocator->alloc(17);
	assert(!ptr);
	for(int i=0;i<99;i++) {
		ptr = allocator->alloc(16);
		v.push_back(ptr);
		assert(ptr);
	}
	allocator->showStats();
	ptr = allocator->alloc(16);
	assert(!ptr);

	std::random_shuffle(v.begin(), v.end());

	for (int i = 0; i < 99; i++) {
		assert(allocator->free(v[i]));
		// assert(ptr);
	}

	allocator->showStats();

	HeapFree(GetProcessHeap(), 0, pHeapMemory);
}