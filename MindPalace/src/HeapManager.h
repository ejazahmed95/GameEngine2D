#pragma once
#include "MemoryBlock.h"

// List of all supported flags
#ifndef SUPPORT_FLAGS
#define SUPPORT_FLAGS
#define SUPPORTS_ALIGNMENT
#define TEST_SINGLE_LARGE_ALLOCATION
#define SUPPORTS_SHOWFREEBLOCKS
#define SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
#endif

// TODO: Override new for this that takes a heap pointer
class HeapManager {
private:
	size_t _heapSize = 0;
	int _numDescriptors = 0;
	MemoryBlock * _head = nullptr, * _tail = nullptr;
	uintptr_t _heapStart = 0;
public:
	HeapManager(void* start, size_t size, int num_descriptors);
	void Initialize(void* start, size_t size, int num_descriptors);
	void* alloc(size_t size);
	void* alloc(size_t size, int alignment);
	bool free(void* dataPtr);
	void coalesce() const;
	bool contains(void* ptr) const;
	size_t getLargestFreeBlock() const;
	bool isAllocated(void* p_ptr) const;
	void showFreeBlocks() const;
	void showOutstandingAllocations() const;
	void debug() const;
	void destroy();
private:
	bool isPowerofTwo(int alignment) const;
	MemoryBlock* getBlockPtrForDataPtr(void* ptr) const;
	MemoryBlock* CreateNewBlock(void* pointer, size_t size);
};

HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors);