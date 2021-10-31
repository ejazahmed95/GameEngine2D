#include "MemoryBlock.h"

#include <iostream>


void* MemoryBlock::getBlockEnd() {
	return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pBaseAddress) + dataSize);
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
	if (free) {
		info[2] = '0';
	} else info[2] = '1';
#endif

}

void MemoryBlock::print() {
	std::cout << "BLOCK " << this << " | " << pBaseAddress << " | ";
	if (free) std::cout << "FREE | ";
	else std::cout << "USED | ";
	std::cout << "DataSize = "<< dataSize << "; SIZE=" << blockSize() << std::endl;
}