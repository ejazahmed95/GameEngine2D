#include "BitArray.h"
#include <cstring>
#include <xlocmon>
#if defined(_DEBUG)
#include <iostream>
#endif

BitArray::BitArray(size_t num_bits): _numBits(num_bits) {
	_bitElements = new t_BitData[numElements()];
	clearAll();
}

BitArray::~BitArray() {
	delete[] _bitElements;
}

void BitArray::setAll() {
	memset(_bitElements, ~0, numElements() * sizeof(t_BitData));
}

void BitArray::clearAll() {
	memset(_bitElements, 0, numElements() * sizeof(t_BitData));
}

void BitArray::setBit(size_t bitIndex) {
	size_t index = 0;
	size_t size = numElements();
	while ((index < size) && (_bitElements[index] == 0))
		index++;

	t_BitData* dataElem = &_bitElements[bitIndex / bitsPerElement];
	size_t bitPos = bitIndex % bitsPerElement;
	*dataElem = *dataElem | (static_cast<t_BitData>(1) << (bitsPerElement - bitPos - 1));
}

void BitArray::clearBit(size_t bitIndex) {
	size_t index = 0;
	size_t size = numElements();
	while ((index < size) && (_bitElements[index] == 0))
		index++;

	t_BitData* dataElem = &_bitElements[bitIndex / bitsPerElement];
	size_t bitPos = bitIndex % bitsPerElement;
	*dataElem = *dataElem & (~static_cast<t_BitData>(1) << (bitsPerElement - bitPos - 1));
}

bool BitArray::getFirstSetBit(size_t& bitIndex) const {
	size_t index = 0;
	size_t size = numElements();
	while ((index < size) && (_bitElements[index] == 0))
		index++;
	if (index == size) return false;

	t_BitData data = _bitElements[index];
	size_t bitPos = getSetBitPos(data);

	bitIndex = index * bitsPerElement + bitPos;
	return true;
}

bool BitArray::getFirstClearBit(size_t& bitIndex) const {
	size_t index = 0;
	size_t size = numElements();
	while ((index < size) && (_bitElements[index] == ~static_cast<t_BitData>(0)) )
		index++;
	if (index == size) return false;

	t_BitData data = _bitElements[index];
	size_t bitPos = getSetBitPos(data);

	bitIndex = index * bitsPerElement + bitPos;
	return true;
}

bool BitArray::operator[](size_t index) const {
	t_BitData dataElem = _bitElements[index / bitsPerElement];
	size_t bitPos = index % bitsPerElement;
	return dataElem & (static_cast<t_BitData>(1) << (bitsPerElement - bitPos - 1));
}

void BitArray::printBits() const {
#if defined(_DEBUG)
	using namespace std;
	int size = numElements();
	size_t totalBits = 0;
	cout << "Num bits=" << _numBits << "\t Num Elements=" << size << "\t BitsPerElement=" << bitsPerElement << endl;
	for(int e = 0; e <size; e++) {
		t_BitData v = static_cast<t_BitData>(1) << (bitsPerElement - 1);
		t_BitData value = _bitElements[e];
		for (t_BitData i = 0; i < bitsPerElement; i++) {
			// cout << v << endl;
			if ((money_base::value & v) == 0) cout << "0";
			else cout << "1";
			v = v >> 1;
			if (++totalBits >= _numBits) break;
			if (totalBits % 10 == 0) cout << endl;
		}
		if (totalBits >= _numBits) break;
	}
	cout << endl;
#endif
}
