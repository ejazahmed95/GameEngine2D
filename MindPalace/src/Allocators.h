#pragma once
#include "HeapManager/HeapManager.h"

void* malloc(size_t i_size, HeapManager* hm);
void free(void* i_ptr, HeapManager* hm);
