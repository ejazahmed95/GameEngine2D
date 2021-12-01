#pragma once

#define DEBUG_BLOCK 0

struct MemoryBlock {
#if DEBUG_BLOCK
	char info[4];
#endif

	void* pBaseAddress;
	MemoryBlock* nextBlock;
	MemoryBlock* prevBlock;
	size_t dataSize;
	bool free;

	void* getBlockEnd();
	size_t blockSize();
	void setDataSize(size_t size);
	void occupy(bool used);
	void print();
};