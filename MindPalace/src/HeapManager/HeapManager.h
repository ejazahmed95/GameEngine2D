#pragma once
#include <cstdint>
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
	bool _allocatorsInitialized = false;
public:
	HeapManager(void* start, size_t size, int num_descriptors);
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
	void initialize(void* start, size_t size, int num_descriptors);
	MemoryBlock* getBlockPtrForDataPtr(void* ptr) const;
	MemoryBlock* CreateNewBlock(void* pointer, size_t size);

// Static variable for testing purposes;
public:
	static HeapManager* instance;
};

HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors);
size_t CalculateAligned(uintptr_t ptr, int alignment);
char* WriteChars(char* ch, const char* str);