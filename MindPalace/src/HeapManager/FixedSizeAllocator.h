#pragma once

struct FSAInfo {
	size_t size;
	size_t numBlocks;
};

class FixedSizeAllocator {
public:
	FixedSizeAllocator(FSAInfo info);
private:
	// BitArray
	size_t _blockSize, _numBlocks;
};