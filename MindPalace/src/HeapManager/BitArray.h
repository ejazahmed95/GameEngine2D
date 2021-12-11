#pragma once
#include <cstdint>
#include "intrin.h"

#if defined(WIN32)
#pragma intrinsic(_BitScanReverse)
typedef uint32_t t_BitData;
#else
#pragma intrinsic(_BitScanReverse64)
typedef uint64_t t_BitData;
#endif

/**
 * Initializes a bit array for number of required bits.
 * Allows setting and clearing bits at bit_index
 */
class BitArray {
public:
	BitArray(size_t num_bits);
	BitArray(size_t num_bits, bool set);
	~BitArray();

	// Copy Constructor
	BitArray(const BitArray& other): _numBits(other._numBits) {
		size_t elementCount = other.numElements();
		_bitElements = new t_BitData[elementCount];
		for(size_t i=0;i<elementCount;i++) {
			_bitElements[i] = other._bitElements[i];
		}
	}
	BitArray& operator=(const BitArray& other) = delete;

	void setAll();
	void clearAll();

	inline bool isBitSet(size_t bitIndex) const {
		return (*this)[bitIndex];
	}

	inline bool isBitClear(size_t bitIndex) const {
		return !(*this)[bitIndex];
	}

	void setBit(size_t bitIndex);
	void clearBit(size_t bitIndex);

	bool getFirstSetBit(size_t& bitIndex) const;
	bool getFirstClearBit(size_t& bitIndex) const;

	bool operator[](size_t index) const;
	void printBits() const;
private:
	inline size_t numElements() const {
		return (_numBits - 1) / bitsPerElement + 1;
	}

	static inline size_t getSetBitPos(t_BitData data) {
		unsigned long pos = 0;
#if defined(WIN32)
		_BitScanReverse(&pos, data);
#else
		_BitScanReverse64(&pos, data);
#endif
		return bitsPerElement - pos - 1;
	}
private:
	t_BitData* _bitElements;
	size_t _numBits;
	constexpr static size_t bitsPerElement = sizeof(t_BitData) * 8;
};

