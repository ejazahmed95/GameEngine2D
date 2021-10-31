#pragma once

#define DEBUG_BLOCK 1
#include <cstdint>

struct MemoryBlock {
#if DEBUG_BLOCK
	char info[4];
#endif

	uint8_t* pBaseAddress;
	size_t dataSize;
	bool free;
	MemoryBlock* nextBlock;

	void* getBlockEnd();
	size_t blockSize();
	void shrink(size_t size);
	void occupy(bool used);
};
 
class HeapManager {
private:
	size_t _heapSize;
	int _numDescriptors;
	MemoryBlock* _memBlocks;
public:
	void* alloc(size_t size);
	void collect();
	MemoryBlock* CreateNewBlock(void* pointer, size_t size);
	void Initialize(void* start, size_t size, int num_descriptors);
};

HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors);
char* WriteChars(char* ch, const char* str);
bool HeapManager_CustomTest(void* heapStart, size_t sizeHeap, int num_descriptors);