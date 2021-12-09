#include <iostream>

#include "TestHelpers.h"

int main() {
	std::cout << "This is the memory manager" << std::endl;
	// HeapManager_CustomTest();

	// HeapTestFinal();


	TestBitArray();
	// TestMemSet();
	// TestBitScans();
	// TestBitToggle();
	// TestNewDelete();
	// RepresentBitsChar(5);

	_CrtDumpMemoryLeaks();
}
