#include "BitArray.h"
#include <intrin.h>
#include <new>
#include <cstring>

BitArray* BitArray::create(size_t num_bits, HeapManager* hm) {
	void* ptr = hm->alloc(sizeof(t_BitData) * ((num_bits - 1) /bitsPerElement + 1));
	return new(ptr) BitArray(num_bits);
}

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
	while ((_bitElements[index] == 0) && (index < size))
		index++;


}

void BitArray::clearBit(size_t bitIndex) {}

bool BitArray::getFirstSetBit(size_t& bitIndex) const {
	size_t index = 0;
	size_t size = numElements();
	while ((_bitElements[index] == 0) && (index < size))
		index++;

	t_BitData data = _bitElements[index];
	size_t bitPos = getSetBitPos(data);

	bitIndex = index * bitsPerElement + bitPos;
	return false;
}

bool BitArray::getFirstClearBit(size_t& bitIndex) const {
	return false;
}

bool BitArray::operator[](size_t index) const {
	return false;
}
