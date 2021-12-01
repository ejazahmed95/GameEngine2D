#include <iostream>
#include <intrin.h>
#include "TestHelpers.h"
#pragma intrinsic(_BitScanForward, _BitScanForward64, _BitScanReverse, _BitScanReverse64)

void TestMemSet() {
	using namespace std;
	std::cout << "Hello World\n";
	uint32_t* values = new uint32_t[10];
	//memset(values, ~0, 10);
	for (int i = 0; i < 10; i++) {
		values[i] = rand();
		cout << "Value:" << values[i] << endl;
	}

	cout << "=======================" << endl;
	memset(values, ~0, 10 * sizeof(uint32_t));

	for (int i = 0; i < 10; i++) {
		cout << "Value:" << values[i] << endl;
	}

	delete[] values;
}

void TestBitScans() {
	using namespace std;
	unsigned long mask = 1026;
	unsigned long forwardIndex = 0;
	unsigned long reverseIndex = 0;

#if WIN32
	_BitScanForward(&forwardIndex, mask);
	_BitScanReverse(&reverseIndex, mask);
#else
	_BitScanForward64(&forwardIndex, mask);
	_BitScanReverse64(&reverseIndex, mask);
#endif
	cout << "Mask: " << mask << "\t Forward Index: " << forwardIndex << "\t Reverse Index: " << reverseIndex << endl;
}
