#pragma once

/**
 * Allocation Statistics
 */
struct AllocStats {
#ifdef _DEBUG
	size_t numAllocs = 0;
	size_t numFrees = 0;
#endif
};
