#include "MemorySystem.h"

#include "HeapManager/FixedSizeAllocator.h"
#include "HeapManager/HeapManager.h"

HeapManager* InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors) {
	// create your HeapManager and FixedSizeAllocators
	auto hm = CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	FSAInfo allocatorsInfo[3] = {FSAInfo(16, 100), FSAInfo(32, 200), FSAInfo(96, 400)};
	hm->initializeFSAs(allocatorsInfo, 3);
	return hm;
}

void Collect(HeapManager* hm) {
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
	hm->coalesce();
}

void DestroyMemorySystem(HeapManager* hm) {
	// Destroy your HeapManager and FixedSizeAllocators
	hm->destroy();
}