#pragma once

size_t CalculateAligned(uintptr_t ptr, int alignment);
char* WriteChars(char* ch, const char* str);
bool HeapManager_CustomTest(void* heapStart, size_t sizeHeap, int num_descriptors);