#include <iostream>
#include <intrin.h>
#include "TestHelpers.h"
#pragma intrinsic(_BitScanForward, _BitScanForward64, _BitScanReverse, _BitScanReverse64)

void RepresentBits(t_TestInt value) {
	using namespace std;
	t_TestInt v = static_cast<t_TestInt>(1) << (sizeof(t_TestInt)*8 - 1);
	for(t_TestInt i = 0; i<sizeof(t_TestInt)*8; i++) {
		// cout << v << endl;
		if ((value & v) == 0) cout << "0";
		else cout << "1";
		v = v >> 1;
	}
	cout << "=============" << endl;
}

void RepresentBitsChar(char value) {
	using namespace std;
	int v = 1 << (sizeof(char) * 8 - 1);
	for (t_TestInt i = 0; i < sizeof(char)*8; i++) {
		cout << static_cast<int>(v) << endl;
		if ((value & v) == 0) cout << "0";
		else cout << "1";
		v = v >> 1;
	}
	cout << endl;
}

void TestMemSet() {
	using namespace std;
	std::cout << "Hello World\n";
	t_TestInt* values = new t_TestInt[10];
	//memset(values, ~0, 10);
	for (int i = 0; i < 10; i++) {
		values[i] = rand();
		cout << "Value:" << values[i] << endl;
	}

	cout << "=======================" << endl;
	memset(values, 128, 10 * sizeof(t_TestInt));

	for (int i = 0; i < 10; i++) {
		RepresentBits(values[i]);
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

void UpdateBit(t_TestInt& data, unsigned int index, bool set);
void TestBitToggle() {
	using namespace std;
	t_TestInt val = 4 + 1; // ...101
	unsigned int setIndex = 1;
	unsigned int clearIndex = 2;

	cout << "Number being tested:: " << val << endl;

	UpdateBit(val, setIndex, true);
	cout << "After setting index=" << setIndex << "; Value=" << val << endl;

	UpdateBit(val, clearIndex, false);
	cout << "After clearing index=" << clearIndex << "; Value=" << val << endl;
}

struct Vec {
	int x, y;
	Vec() : x(1), y(1) {
		std::cout << "Vec constructor called" << std::endl;
	}
	~Vec() {
		std::cout << "Vec destroyed\n";
	}
};
void TestNewDelete() {
	Vec* v = new Vec();
	delete v;

	std::cout << "===== Array construction and destruction ======" << std::endl;

	Vec* vArr = new Vec[5];
	delete[] vArr;
}

void UpdateBit(t_TestInt& data, unsigned int index, bool set) {
	if(set)
		data |= (static_cast<t_TestInt>(1) << index);
	else
		data &= ~(static_cast<t_TestInt>(1) << index);
}
