#include "FixedSizeAllocator.h"

FixedSizeAllocator::FixedSizeAllocator(FSAInfo info): _blockSize(info.size), _numBlocks(info.numBlocks) {
	
}

void* FixedSizeAllocator::alloc(size_t size) {
	return nullptr;
}

bool FixedSizeAllocator::free(void* data_ptr) {
	return false;
}

void FixedSizeAllocator::destroy() {
#if DEBUG
	// Print existing allocations
#else
#endif
	// Cleanup all memory
}

void FixedSizeAllocator::showOutstandingBlocks() const {
	
}

void FixedSizeAllocator::showFreeBlocks() const {}
