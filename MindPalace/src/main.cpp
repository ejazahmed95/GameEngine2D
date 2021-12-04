#include <cassert>
#include <cinttypes>
#include <iostream>
#include "TestHelpers.h"
#include "Windows.h"

int main() {
	std::cout << "This is the memory manager" << std::endl;
	// HeapManager_CustomTest();

	HeapTestFinal();


	// TestMemSet();
	// TestBitScans();
	// TestBitToggle();
	// TestNewDelete();

	_CrtDumpMemoryLeaks();
}
