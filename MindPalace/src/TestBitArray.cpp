#include <cassert>
#include <iostream>
#include <Windows.h>

#include "MemorySystem.h"
#include "TestHelpers.h"

void TestBitArray() {
	using namespace std;

	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, 1024 * 10);
	assert(pHeapMemory);
	// Create your HeapManager and FixedSizeAllocators.
	auto hm = CreateHeapManager(pHeapMemory, 1024 * 10, 0);

	// TestMemSet();

	srand(time(NULL));
	BitArray* ba = new BitArray(100);
	ba->printBits();

	size_t firstClearBit = -1, firstSetBit = -1;
	if (ba->getFirstClearBit(firstClearBit)) {
		cout << "First cleared bit index=" << firstClearBit << endl;
	}
	else {
		cout << "There is no clear bit available" << endl;
	}

	cout << "Setting Random Indices..." << endl;
	for(int i=0;i<20;i++) {
		int index = rand() % 100;
		ba->setBit(index);
		std::cout << "Set Index=" << index << endl;
		assert((*ba)[index]);
	}
	ba->setBit(99);

	ba->printBits();

	if(ba->getFirstSetBit(firstSetBit)) {
		cout << "First set bit index=" << firstSetBit << endl;
	} else {
		cout << "There is no set bit available" << endl;
	}

	


	HeapFree(GetProcessHeap(), 0, pHeapMemory);
}