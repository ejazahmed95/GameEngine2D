#include "MemorySystem.h"
#include "HeapManager/HeapManager.h"

HeapManager* InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors) {
	// create your HeapManager and FixedSizeAllocators
	auto hm = CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	return hm;
}

void Collect(HeapManager* hm) {
	hm->coalesce();
	// hm->debug();
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem(HeapManager* hm) {
	// Destroy your HeapManager and FixedSizeAllocators
	hm->destroy();
}