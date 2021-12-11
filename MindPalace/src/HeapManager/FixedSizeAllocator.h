#pragma once
#include "AllocStats.h"
#include "BitArray.h"

struct FSAInfo {
	size_t size;
	size_t numBlocks;
	uintptr_t startLoc;
	FSAInfo(size_t size, size_t numBlocks) : size(size), numBlocks(numBlocks), startLoc(0) {}
};

/**
 * Creates an allocator of fixed size. The required memory is already allocated and passed through the constructor
 */
class FixedSizeAllocator {
public:
	FixedSizeAllocator(FSAInfo info);
	~FixedSizeAllocator();
	FixedSizeAllocator(const FixedSizeAllocator& other) = delete;
	FixedSizeAllocator& operator=(const FixedSizeAllocator& other) = delete;
	void* alloc(size_t size);
	bool free(void* dataPtr);
	void destroy();
	bool contains(void* dataPtr) const;
	void showOutstandingBlocks() const;
	void showFreeBlocks() const;
	static size_t getRequiredMemory(FSAInfo& info);
	void showStats() const;
private:
	// BitArray
	size_t _blockSize, _numBlocks;
	BitArray* _freeList;
#if defined(_DEBUG)
	AllocStats _stats;
#endif
public:
	const uintptr_t _startLoc;
};