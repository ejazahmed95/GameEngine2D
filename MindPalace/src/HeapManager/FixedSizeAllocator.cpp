#include "FixedSizeAllocator.h"

FixedSizeAllocator::FixedSizeAllocator(FSAInfo info): _blockSize(info.size), _numBlocks(info.numBlocks) {
	
}
