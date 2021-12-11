#include "FixedSizeAllocator.h"

#include <iostream>

FixedSizeAllocator::FixedSizeAllocator(FSAInfo info): _blockSize(info.size), _numBlocks(info.numBlocks), _startLoc(info.startLoc) {
	_freeList = new BitArray(_numBlocks, true);
	_freeList->clearBit(0);
}

FixedSizeAllocator::~FixedSizeAllocator() {
	delete _freeList;
}

void* FixedSizeAllocator::alloc(size_t size) {
	if (size > _blockSize) return nullptr;
	size_t bitIndex = 0;
	if (!_freeList->getFirstSetBit(bitIndex)) return nullptr;
#ifdef _DEBUG
	if ((*_freeList)[bitIndex]) _stats.numAllocs++;
#endif
	_freeList->clearBit(bitIndex);
	return reinterpret_cast<void*>(_startLoc + bitIndex * _blockSize);
}

bool FixedSizeAllocator::free(void* dataPtr) {
	if (!contains(dataPtr)) return false;
	uintptr_t diff = reinterpret_cast<uintptr_t>(dataPtr) - _startLoc;
	size_t index = diff / _blockSize;
#ifdef _DEBUG
	if (!(*_freeList)[index]) _stats.numFrees++;
#endif
	_freeList->setBit(index);
	return true;
}

void FixedSizeAllocator::destroy() {
#if defined(_DEBUG)
	// Print existing allocations
#else
#endif
	// Cleanup all memory
	_freeList->clearAll();
}

bool FixedSizeAllocator::contains(void* dataPtr) const {
	auto loc = reinterpret_cast<uintptr_t>(dataPtr) - _startLoc;
	return loc > 0 && loc % _blockSize == 0 && (loc / _blockSize) < _numBlocks;
}

void FixedSizeAllocator::showOutstandingBlocks() const {
	showStats();
	// _freeList->printBits();
}

void FixedSizeAllocator::showFreeBlocks() const {
	showStats();
	// _freeList->printBits();
}

size_t FixedSizeAllocator::getRequiredMemory(FSAInfo& info) {
	return info.numBlocks * info.size;
}

void FixedSizeAllocator::showStats() const {
#ifdef _DEBUG
	std::cout << "FSA: BlockSize = " << _blockSize << " | Num Blocks = " << _numBlocks;
	std::cout << "Total Allocs = "<<_stats.numAllocs << " | Total Frees = " << _stats.numFrees << std::endl;
#endif
}
