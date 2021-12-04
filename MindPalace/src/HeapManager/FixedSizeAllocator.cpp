#include "FixedSizeAllocator.h"

#include "HeapManager.h"

FixedSizeAllocator::FixedSizeAllocator(FSAInfo info): _blockSize(info.size), _numBlocks(info.numBlocks), _startLoc(info.startLoc) {
	_freeList = new BitArray(_numBlocks);
	_freeList->setAll();
	_freeList->clearBit(0);
}

FixedSizeAllocator::~FixedSizeAllocator() {
	delete _freeList;
}

void* FixedSizeAllocator::alloc(size_t size) {
	if (size > _blockSize) return nullptr;
	size_t bitIndex = 0;
	if (!_freeList->getFirstSetBit(bitIndex)) return nullptr;
	_freeList->clearBit(bitIndex);
	return reinterpret_cast<void*>(_startLoc + bitIndex * _blockSize);
}

bool FixedSizeAllocator::free(void* dataPtr) {
	if (!contains(dataPtr)) return false;
	ptrdiff_t diff = reinterpret_cast<uintptr_t>(dataPtr) - _startLoc;

	_freeList->setBit(diff / _blockSize);
	return false;
}

void FixedSizeAllocator::destroy() {
#if DEBUG
	// Print existing allocations
#else
#endif
	// Cleanup all memory
	_freeList->clearAll();
}

bool FixedSizeAllocator::contains(void* dataPtr) {
	ptrdiff_t diff = reinterpret_cast<uintptr_t>(dataPtr);
	return diff > 0 && diff % _blockSize == 0 && (diff / _blockSize) < _numBlocks;
}

void FixedSizeAllocator::showOutstandingBlocks() const {
	
}

void FixedSizeAllocator::showFreeBlocks() const {}
