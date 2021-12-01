#pragma once
#include "HeapManager/HeapManager.h"

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
HeapManager* InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect(HeapManager* hm);

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem(HeapManager* hm);
