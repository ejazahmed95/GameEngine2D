#include <cinttypes>
// #include <malloc.h>
#include "HeapManager/HeapManager.h"

#include <cstdio>


void* malloc(size_t i_size, HeapManager* hm) {
	// replace with calls to your HeapManager or FixedSizeAllocators
	// printf("malloc %zu\n", i_size);
	return hm->alloc(i_size);
	// return _aligned_malloc(i_size, 4);
}

void __cdecl free(void* i_ptr, HeapManager* hm) {
	// replace with calls to your HeapManager or FixedSizeAllocators
	// printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	hm->free(i_ptr);
	// return _aligned_free(i_ptr);
}
//
// void* operator new(size_t i_size) {
// 	// replace with calls to your HeapManager or FixedSizeAllocators
// 	printf("new %zu\n", i_size);
// 	return _aligned_malloc(i_size, 4);
// }
//
// void operator delete(void* i_ptr) {
// 	// replace with calls to your HeapManager or FixedSizeAllocators
// 	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
// 	return _aligned_free(i_ptr);
// }
//
// void* operator new[](size_t i_size) {
// 	// replace with calls to your HeapManager or FixedSizeAllocators
// 	printf("new [] %zu\n", i_size);
// 	return _aligned_malloc(i_size, 4);
// }
//
// void operator delete [](void* i_ptr) {
// 	// replace with calls to your HeapManager or FixedSizeAllocators
// 	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
// 	return _aligned_free(i_ptr);
// }
