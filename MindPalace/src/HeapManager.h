#pragma once
#include "MemoryBlock.h"

// TODO: Override new for this that takes a heap pointer
class HeapManager {
private:
	size_t _heapSize;
	int _numDescriptors;
	MemoryBlock *_head, *_tail;
	uintptr_t _heapStart;
public:
	void Initialize(void* start, size_t size, int num_descriptors);
	void* alloc(size_t size);
	void* alloc(size_t size, int alignment);
	void free(void* dataPtr);
	void coalesce();
	void debug();
private:
	MemoryBlock* CreateNewBlock(void* pointer, size_t size);
};

HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors);