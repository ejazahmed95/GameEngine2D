#pragma once
#include "BitArray.h"

struct FSAInfo {
	size_t size;
	size_t numBlocks;
	uintptr_t startLoc;
	FSAInfo(size_t size, size_t numBlocks) : size(size), numBlocks(numBlocks), startLoc(0) {}
};

class FixedSizeAllocator {
public:
	FixedSizeAllocator(FSAInfo info);
	~FixedSizeAllocator();
	void* alloc(size_t size);
	bool free(void* dataPtr);
	void destroy();
	bool contains(void* dataPtr);
	void showOutstandingBlocks() const;
	void showFreeBlocks() const;
private:
	// BitArray
	size_t _blockSize, _numBlocks;
	BitArray* _freeList;
public:
	const uintptr_t _startLoc;
};