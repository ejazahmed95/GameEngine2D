#pragma once

struct FSAInfo {
	size_t size;
	size_t numBlocks;
	FSAInfo(size_t size, size_t numBlocks) : size(size), numBlocks(numBlocks) {};
};

class FixedSizeAllocator {
public:
	FixedSizeAllocator(FSAInfo info);
	void* alloc(size_t size);
	bool free(void* data_ptr);
private:
	// BitArray
	size_t _blockSize, _numBlocks;
};