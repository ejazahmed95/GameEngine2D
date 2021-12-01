#pragma once
#include <cstdint>

class BitArray {
public:
#if WIN32
	typedef uint32_t _bitData;
#else
	typedef uint64_t t_bitData;
#endif

	BitArray(size_t num_bits, bool initToZero);

private:
	t_bitData* m_pBits;
	const size_t bitsPerElement = sizeof(t_bitData) * 8;
};
