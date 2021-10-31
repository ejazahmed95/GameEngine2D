#include "HeapManager.h"

#include <cassert>
#include <iostream>

void* MemoryBlock::getBlockEnd() {
	return pBaseAddress + dataSize;
}

size_t MemoryBlock::blockSize() {
	return dataSize + sizeof(MemoryBlock);
}

void MemoryBlock::shrink(size_t size) {
	dataSize = size;
}

void MemoryBlock::occupy(bool used) {
	free = !used;
#if DEBUG_BLOCK
	if(free) {
		info[2] = '0';
	} else info[2] = '1';
#endif

}

void* HeapManager::alloc(size_t size) {
	MemoryBlock* prevBlock = _memBlocks;
	MemoryBlock* currBlock = _memBlocks->nextBlock;
	while(currBlock != nullptr) {
		if(currBlock->free && currBlock->dataSize > size) {
			size_t currBlockSize = currBlock->blockSize();
			
			currBlock->shrink(size); // Use Alignment
			currBlock->getBlockEnd();
			size_t remSize = currBlockSize - currBlock->blockSize();
			MemoryBlock* newBlock = CreateNewBlock(currBlock->getBlockEnd(), remSize);
			if(newBlock != nullptr) {
				newBlock->nextBlock = currBlock->nextBlock;
				currBlock->nextBlock = newBlock;
			}
			currBlock->occupy(true);
			break;
			// Split the current block
			// Remove from free list
			// Give the current block
			// Create a new block from remaining
		}
		prevBlock = currBlock;
		currBlock = currBlock->nextBlock;
	}
	if (currBlock == nullptr) return nullptr;
	return currBlock->pBaseAddress;
}

void HeapManager::collect() {

}

MemoryBlock* HeapManager::CreateNewBlock(void* pointer, size_t size) {
	// assert(size > sizeof(MemoryBlock));

	if (size < sizeof(MemoryBlock)) return nullptr;

	MemoryBlock* block = reinterpret_cast<MemoryBlock*>(pointer);
	
	block->pBaseAddress = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(pointer) + sizeof(MemoryBlock));
	block->dataSize = size - sizeof(MemoryBlock);
	block->nextBlock = nullptr;
	block->free = true;

#ifdef DEBUG_BLOCK
	block->info[0] = 'M';
	block->info[1] = 'B';
	block->info[2] = '0';
	block->info[3] = '\0';
#endif

	return block;
}

void HeapManager::Initialize(void* start, size_t size, int num_descriptors) {
	_heapSize = size;
	_numDescriptors = num_descriptors;

	_memBlocks = CreateNewBlock(start, sizeof(MemoryBlock));
	MemoryBlock* firstFreeBlock = CreateNewBlock(_memBlocks->getBlockEnd(), size - 3*_memBlocks->blockSize());
	MemoryBlock* endBlock = CreateNewBlock(firstFreeBlock->getBlockEnd(), sizeof(MemoryBlock));

	_memBlocks->occupy(true);
	endBlock->occupy(true);

	_memBlocks->nextBlock = firstFreeBlock;
	firstFreeBlock->nextBlock = endBlock;
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

HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, int numDescriptors) {
	char* ch = static_cast<char*>(pHeapMemory);
	ch = WriteChars(ch, "HEAP");
	HeapManager* hm = (HeapManager*)(ch);
	size_t hSize = sizeof(HeapManager) + static_cast<size_t>(8);

	std::cout << "HSize=" << hSize << "||| Available Size=" << heapSize - hSize << std::endl;
	std::cout << "Start mem location = " << pHeapMemory << std::endl;
	hm->Initialize(static_cast<char*>(pHeapMemory) + hSize, heapSize - hSize, numDescriptors);
	ch += sizeof(HeapManager);
	ch = WriteChars(ch, "HEAP");

	return hm;
}
