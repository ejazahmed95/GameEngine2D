#pragma once
#include <cstdint>
#include "intrin.h"

#include "HeapManager.h"

#pragma intrinsic(_BitScanReverse, _BitScanReverse64)

#if WIN32
typedef uint32_t t_BitData;
#else
typedef uint64_t t_BitData;
#endif

class BitArray {
public:
	static BitArray* create(size_t num_bits, HeapManager* hm);
	BitArray(size_t num_bits);
	~BitArray();

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
private:
	inline size_t numElements() const {
		return (_numBits - 1) / bitsPerElement + 1;
	}

	static inline size_t getSetBitPos(t_BitData data) {
		unsigned long pos;
#if WIN32
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

