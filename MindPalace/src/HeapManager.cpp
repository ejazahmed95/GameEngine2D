#include "HeapManager.h"


#include "TestHelpers.h"
#include <cassert>
#include <iostream>
#include <Windows.h>

HeapManager* CreateHeapManager(size_t heapSize, int numDescriptors) {
#ifdef USE_HEAP_ALLOC
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, heapSize);
#else
	// Get SYSTEM_INFO, which includes the memory page size
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	// round our size to a multiple of memory page size
	assert(SysInfo.dwPageSize > 0);
	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((heapSize + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif
	assert(heapSize > sizeof(HeapManager));
	assert(pHeapMemory);
	
	const auto hm = new(pHeapMemory) HeapManager(pHeapMemory, heapSize, numDescriptors);
	return hm;
}

void DestroyHeapManager(HeapManager* hm) {
	if (hm) {
		hm->destroy();
#ifdef USE_HEAP_ALLOC
		HeapFree(GetProcessHeap(), 0, hm);
#else
		VirtualFree(hm, 0, MEM_RELEASE);
#endif
	}
}

HeapManager::HeapManager(void* start, size_t size, int num_descriptors) {
	constexpr size_t headerSize = sizeof(HeapManager);
	Initialize(static_cast<char*>(start) + headerSize, size - headerSize, num_descriptors);
}

void HeapManager::Initialize(void* start, size_t size, int num_descriptors) {
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
	// assert(isPowerofTwo(alignment));
	if(!isPowerofTwo(alignment)) {
		return nullptr;
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
				return newBlock->pBaseAddress;
			}
		}
		curr = next;
		next = next->prevBlock;
	}
	return nullptr;
}

bool HeapManager::free(void* dataPtr) {
	uintptr_t ptr = reinterpret_cast<uintptr_t>(dataPtr) - sizeof(MemoryBlock);
	MemoryBlock* mb = reinterpret_cast<MemoryBlock*>(ptr);
	mb->occupy(false);
	return true;
}

void HeapManager::coalesce() {
	MemoryBlock* curr = _head;
	MemoryBlock* next = curr->nextBlock;

	// Handling the empty space after head and first block
	if (next->free) {
		auto nb = next->nextBlock;
		next = CreateNewBlock(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_head) + _head->blockSize()), sizeof(MemoryBlock));
		next->nextBlock = nb; nb->prevBlock = next;
		next->prevBlock = curr; curr->nextBlock = next;

		next->setDataSize(reinterpret_cast<uintptr_t>(next->nextBlock) - reinterpret_cast<uintptr_t>(next) - sizeof(MemoryBlock));
	}
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

	std::cout << "============== Printing All Blocks 2 ===================" << std::endl;
	MemoryBlock* mb = _tail;
	while (mb != nullptr) {
		mb->print();
		mb = mb->prevBlock;
	}
	std::cout << "=================================" << std::endl;
}

void HeapManager::destroy() {}

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

bool HeapManager::isPowerofTwo(int alignment) const {
	// Bitwise AND operator will return 0 if alignment is a power of 2.
	if (alignment == 0) return false;
	return !(alignment & (alignment - 1));
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
	std::cout << "============== Printing All Free Blocks ===================" << std::endl;
	MemoryBlock* mb = _head->nextBlock;
	while (mb != nullptr && mb != _tail) {
		if(mb->free) mb->print();
		mb = mb->nextBlock;
	}
	std::cout << "=============== ** END ** ==================" << std::endl;
}

void HeapManager::showOutstandingAllocations() const {
	std::cout << "============== Printing All Outstanding Blocks ===================" << std::endl;
	MemoryBlock* mb = _head->nextBlock;
	while (mb != nullptr && mb != _tail) {
		if (!mb->free) mb->print();
		mb = mb->nextBlock;
	}
	std::cout << "=============== ** END ** ==================" << std::endl;
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

	// std::cout << "Size and Mem block size: " << block->dataSize << std::endl;
	// block->print();

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
