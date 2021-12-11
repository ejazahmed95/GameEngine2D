#include "HeapManager.h"
#include <new>

#ifdef _DEBUG
#include <iostream>
#endif

HeapManager* HeapManager::instance = nullptr;


HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors) {
	if (HeapManager::instance == nullptr) {
		HeapManager::instance = new(pHeapMemory) HeapManager(pHeapMemory, heapSize, numDescriptors);
	}
	return HeapManager::instance;
}

HeapManager::HeapManager(void* start, size_t size, int num_descriptors) {
	constexpr size_t headerSize = sizeof(HeapManager);
	initialize(static_cast<char*>(start) + headerSize, size - headerSize, num_descriptors);
}

void HeapManager::initializeFSAs(FSAInfo* fsaInfos, size_t size) {
	auto allocators = new FixedSizeAllocator*[size];
	for(size_t i=0;i<size;i++) {
		FSAInfo info = fsaInfos[i];
		info.startLoc = reinterpret_cast<uintptr_t>(alloc(info.size * info.numBlocks));
		allocators[i] = new FixedSizeAllocator(info);
	}
	_allocators = allocators;
	_numAllocators = size;
}

void HeapManager::initialize(void* start, size_t size, int num_descriptors) {
	_heapSize = size;
	_numDescriptors = num_descriptors;
	_heapStart = reinterpret_cast<uintptr_t>(start);

	_head = CreateNewBlock(start, sizeof(MemoryBlock));
	MemoryBlock* firstFreeBlock = CreateNewBlock(_head->getBlockEnd(), size - 3 * _head->blockSize());
	_tail = CreateNewBlock(firstFreeBlock->getBlockEnd(), sizeof(MemoryBlock));

	_head->occupy(true);
	_tail->occupy(true);

	_head->nextBlock = firstFreeBlock;
	firstFreeBlock->nextBlock = _tail;

	_tail->prevBlock = firstFreeBlock;
	firstFreeBlock->prevBlock = _head;
}

void* HeapManager::alloc(size_t size) {
	return alloc(size, 4);
}

void* HeapManager::alloc(size_t size, int alignment) {
	MemoryBlock* curr = _tail;
	MemoryBlock* next = _tail->prevBlock;

	for(size_t i=0;i < _numAllocators;i++) {
		void* ptr = _allocators[i]->alloc(size);
		if (ptr != nullptr) return ptr;
	}

	while(next != nullptr) {
		if(next->free) {
			size_t availableSize = reinterpret_cast<uintptr_t>(curr) - reinterpret_cast<uintptr_t>(next);
			size_t alignedSize = size;
			alignedSize += CalculateAligned(reinterpret_cast<uintptr_t>(curr) - size, alignment);

			// std::cout << "Available Size = " << availableSize << " ; alignedSize = " << alignedSize << std::endl;
			if(availableSize > (alignedSize + sizeof(MemoryBlock))) {
				size_t remainingSize = availableSize - (alignedSize + sizeof(MemoryBlock));

				// Store this as new block can potentially override the value for next block
				MemoryBlock* prevBlockOfNext = next->prevBlock;

				MemoryBlock* newBlock = CreateNewBlock(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(curr) - alignedSize - sizeof(MemoryBlock)), alignedSize + sizeof(MemoryBlock));
				newBlock->occupy(true);

				curr->prevBlock = newBlock;
				newBlock->nextBlock = curr;
				
				if(remainingSize <= sizeof(MemoryBlock)) { // Next variable is potentially overriden 
					newBlock->prevBlock = prevBlockOfNext;
					newBlock->prevBlock->nextBlock = newBlock;
				} else {
					newBlock->prevBlock = next;
					next->nextBlock = newBlock;

					size_t newSize = reinterpret_cast<uintptr_t>(newBlock) - reinterpret_cast<uintptr_t>(next) - sizeof(MemoryBlock);
					next->setDataSize(newSize);
				}
#ifdef _DEBUG
				_allocStats.numAllocs++;
#endif
				return newBlock->pBaseAddress;
			}
		}
		curr = next;
		next = next->prevBlock;
	}
	return nullptr;
}

bool HeapManager::free(void* dataPtr) {
	for(size_t i =0; i<_numAllocators; i++) {
		if(_allocators[i]->free(dataPtr)) return true;
	}
	if (!contains(dataPtr)) return false;
	MemoryBlock* mb = getBlockPtrForDataPtr(dataPtr);
	mb->occupy(false);
#ifdef _DEBUG
	_allocStats.numFrees++;
#endif
	return true;
}

void HeapManager::coalesce() const {
	MemoryBlock* curr = _head;
	MemoryBlock* next = curr->nextBlock;
	while(next != _tail) {
		if(curr->free && next->free) {
			curr->nextBlock = next->nextBlock;
			next->nextBlock->prevBlock = curr;
			uintptr_t diff = reinterpret_cast<uintptr_t>(curr->nextBlock) - reinterpret_cast<uintptr_t>(curr);
			// if (a < sizeof(MemoryBlock)) std::cout << "AAA:: " << a << " | " << curr << " | " << curr->nextBlock << std::endl;
			curr->setDataSize(diff - sizeof(MemoryBlock));
		} else {
			curr = curr->nextBlock;
		}
		next = curr->nextBlock;
	}
}

void HeapManager::debug() const {
	// std::cout << "============== Printing All Blocks ===================" << std::endl;
	// MemoryBlock* mb = _head;
	// while(mb != nullptr) {
	// 	mb->print();
	// 	mb = mb->nextBlock;
	// }
	// std::cout << "=================================" << std::endl;

#ifdef _DEBUG
	std::cout << "============== Printing All Blocks 2 ===================" << std::endl;
	MemoryBlock* mb = _tail;
	while (mb != nullptr) {
		mb->print();
		mb = mb->prevBlock;
	}
	std::cout << "=================================" << std::endl;
#endif
}

void HeapManager::destroy() {
	for(size_t i=0;i<_numAllocators;i++) {
		_allocators[i]->destroy();
		free(reinterpret_cast<void*>(_allocators[i]->_startLoc));
		delete _allocators[i];
	}
	delete[] _allocators;
#ifdef _DEBUG
	std::cout << "Heap Manager Destroyed!" << std::endl;
	if(_allocStats.numAllocs != _allocStats.numFrees) {
		showOutstandingAllocations();
	} else {
		std::cout << "Congratulations! No Outstanding Allocations" << std::endl;
	}
#endif
}

void HeapManager::showStats() const {
#ifdef _DEBUG
	std::cout << "==============Showing Heap Manager Stats!!!==============" << std::endl;
	std::cout << "Total Allocs = " << _allocStats.numAllocs << " | Total Frees = " << _allocStats.numFrees << std::endl;
	for (size_t i = 0; i < _numAllocators; i++) {
		_allocators[i]->showStats();
	}
	std::cout << "============== ** END ** ==============" << std::endl;
#endif
}

bool HeapManager::contains(void* ptr) const {
	MemoryBlock* block = _head->nextBlock;
	const auto ptrLoc = getBlockPtrForDataPtr(ptr);
	while (block) {
		if(block == ptrLoc) {
			return true;
		}
		block = block->nextBlock;
	}
	return false;
}

MemoryBlock* HeapManager::getBlockPtrForDataPtr(void* ptr) const {
	return reinterpret_cast<MemoryBlock*>(reinterpret_cast<uintptr_t>(ptr) - sizeof(MemoryBlock));
}

size_t HeapManager::getLargestFreeBlock() const {
	size_t largestBlockSize = 0;
	MemoryBlock* block = _head->nextBlock;
	while(block) {
		if (block->free && block->dataSize > largestBlockSize) largestBlockSize = block->dataSize;
		block = block->nextBlock;
	}
	return largestBlockSize;
}

bool HeapManager::isAllocated(void* p_ptr) const {
	if(contains(p_ptr)) {
		MemoryBlock* blockPtr = getBlockPtrForDataPtr(p_ptr);
		return !blockPtr->free;
	}
	return true;
}

void HeapManager::showFreeBlocks() const {
#ifdef _DEBUG
	std::cout << "============== Printing All Free Blocks ===================" << std::endl;
	for (size_t i = 0; i < _numAllocators; i++) {
		_allocators[i]->showFreeBlocks();
	}
	MemoryBlock* mb = _head->nextBlock;
	while (mb != nullptr && mb != _tail) {
		if(mb->free) mb->print();
		mb = mb->nextBlock;
	}
	std::cout << "=============== ** END ** ==================" << std::endl;
#endif
}

void HeapManager::showOutstandingAllocations() const {
#ifdef _DEBUG
	std::cout << "============== Printing All Outstanding Blocks ===================" << std::endl;
	for (size_t i = 0; i < _numAllocators; i++) {
		_allocators[i]->showOutstandingBlocks();
	}
	MemoryBlock* mb = _head->nextBlock;
	while (mb != nullptr && mb != _tail) {
		if (!mb->free) mb->print();
		mb = mb->nextBlock;
	}
	std::cout << "=============== ** END ** ==================" << std::endl;
#endif
}


MemoryBlock* HeapManager::CreateNewBlock(void* pointer, size_t size) {
	// assert(size > sizeof(MemoryBlock));

	if (size < sizeof(MemoryBlock)) return nullptr;

	
	MemoryBlock* block = static_cast<MemoryBlock*>(pointer);
	
	block->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pointer) + sizeof(MemoryBlock));
	block->dataSize = size - sizeof(MemoryBlock);
	block->nextBlock = nullptr;
	block->prevBlock = nullptr;
	block->free = true;

#if DEBUG_BLOCK
	block->info[0] = 'M';
	block->info[1] = 'B';
	block->info[2] = '0';
	block->info[3] = '\0';
#endif

	return block;
}

char* WriteChars(char* ch, const char* str) {
	int i = 0;
	while(str[i] != '\0') {
		*ch = str[i];
		ch++;
		i++;
	}
	return ch;
}

size_t CalculateAligned(uintptr_t ptr, int alignment) {
	return (ptr + alignment) % alignment;
}
