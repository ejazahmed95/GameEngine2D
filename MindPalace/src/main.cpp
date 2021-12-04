#include <iostream>

#include "TestHelpers.h"

int main() {
	std::cout << "This is the memory manager" << std::endl;
	// HeapManager_CustomTest();

	HeapTestFinal();


	// TestMemSet();
	// TestBitScans();
	// TestBitToggle();
	// TestNewDelete();
	// RepresentBitsChar(5);

	_CrtDumpMemoryLeaks();
}
