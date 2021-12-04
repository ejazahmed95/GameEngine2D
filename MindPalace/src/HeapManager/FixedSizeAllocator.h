#pragma once
#include "BitArray.h"
#include "HeapManager.h"

struct FSAInfo {
	size_t size;
	size_t numBlocks;
	FSAInfo(size_t size, size_t numBlocks) : size(size), numBlocks(numBlocks) {};
};

class FixedSizeAllocator {
public:
	FixedSizeAllocator(FSAInfo info);
private:
	// BitArray
	size_t _blockSize, _numBlocks;
};