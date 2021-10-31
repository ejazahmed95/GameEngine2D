#include <cassert>
#include <cinttypes>
#include <iostream>

#include "HeapManager.h"

int main() {
	const size_t sizeHeap = 1024*32;
	const size_t bufferSize = 32;
	std::cout << "This is the memory manager" << std::endl;

	void* const heap = malloc(sizeHeap + bufferSize*2);

	char* ch = static_cast<char*>(heap);
	assert(ch);

	// Initializing the memory for debugging purposes
	for (int i=0; i<bufferSize; i++) {
		*ch = '=';
		ch++;
	}
	void* heapStart = ch;
	for(int i =0;i<sizeHeap;i++) {
		*ch = ' ';
		ch++;
	}
	for (int i = 0; i < bufferSize; i++) {
		*ch = '=';
		ch++;
	}
	ch = static_cast<char*>(heapStart);
	std::cout << heapStart << std::endl;
	HeapManager_CustomTest(heapStart, sizeHeap, 1024);

	free(heap);

	// SYSTEM_INFO SysInfo;
	// GetSystemInfo(&SysInfo);
	// round our size to a multiple of memory page size
	// size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	// void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	// assert(pHeapMemory);
	// VirtualFree(pHeapMemory, 0, MEM_RELEASE);
}