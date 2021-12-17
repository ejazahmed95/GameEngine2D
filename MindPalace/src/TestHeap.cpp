#include "HeapManager.h"
#include <Windows.h>

#include <assert.h>
#include <algorithm>
#include <vector>

bool HeapManager_CustomTest() {
	const size_t sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Self Heap Test
	HeapManager* pHeapManager = CreateHeapManager(sizeHeap, numDescriptors);
	assert(pHeapManager);

	if (pHeapManager == nullptr)
		return false;

#ifdef TEST_SINGLE_LARGE_ALLOCATION
	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
	{
#ifdef SUPPORTS_SHOWFREEBLOCKS
		pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS

		size_t largestBeforeAlloc = pHeapManager->getLargestFreeBlock();
		void* pPtr = pHeapManager->alloc(largestBeforeAlloc);

		if (pPtr) {
#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
			printf("After large allocation:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
			pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			pHeapManager->showOutstandingAllocations();
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			printf("\n");
#endif

			size_t largestAfterAlloc = pHeapManager->getLargestFreeBlock();
			bool success = pHeapManager->contains(pPtr) && pHeapManager->isAllocated(pPtr);
			assert(success);

			success = pHeapManager->free(pPtr);
			assert(success);

			pHeapManager->coalesce();

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
			printf("After freeing allocation and garbage collection:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
			pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			pHeapManager->showOutstandingAllocations();
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			printf("\n");
#endif

			size_t largestAfterCollect = pHeapManager->getLargestFreeBlock();
		}
	}
#endif

	std::vector<void*> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	do {
		const size_t		maxTestAllocationSize = 1024;

		size_t	sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

#ifdef SUPPORTS_ALIGNMENT
		// pick an alignment
		const unsigned int	alignments[] = { 4, 8, 16, 32 };

		const unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

		const unsigned int	alignment = alignments[index];

		void* pPtr = pHeapManager->alloc(sizeAlloc, alignment);

		// check that the returned address has the requested alignment
		assert((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0);
#else
		void* pPtr = hm->alloc(sizeAlloc);
#endif // SUPPORT_ALIGNMENT

		// if allocation failed see if garbage collecting will create a large enough block
		if (pPtr == nullptr) {
			pHeapManager->coalesce();

#ifdef SUPPORTS_ALIGNMENT
			pPtr = pHeapManager->alloc(sizeAlloc, alignment);
#else
			pPtr = hm->alloc(sizeAlloc);
#endif // SUPPORT_ALIGNMENT

			// if not we're done. go on to cleanup phase of test
			if (pPtr == nullptr)
				break;
		}
		// std::cout << "Pointer found:" << pPtr << " || Size:: " << sizeAlloc << " || Alignment::" << alignment << std::endl;
		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		// randomly free and/or garbage collect during allocation phase
		const unsigned int freeAboutEvery = 10;
		const unsigned int garbageCollectAboutEvery = 40;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0)) {
			void* pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager->contains(pPtr) && pHeapManager->isAllocated(pPtr);
			// if (!success) {
			// 	std::cout << "Pointer in question is::" << pPtr << std::endl;
			// 	std::cout << "Pointer in question is::" << pHeapManager->contains(pPtr) << std::endl;
			// 	std::cout << "Pointer in question is::" << pHeapManager->isAllocated(pPtr) << std::endl;
			// 	pHeapManager->debug();
			// }
			assert(success);

			// std::cout << "Freeing Pointer::" << pPtr << std::endl;
			
			success = pHeapManager->free(pPtr);
			assert(success);

			numFrees++;
		}

		if ((rand() % garbageCollectAboutEvery) == 0) {
			pHeapManager->coalesce();

			numCollects++;
		}

		// Testing Code
		// pHeapManager->debug();

	} while (1);

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
	printf("After exhausting allocations:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
	pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
	pHeapManager->showOutstandingAllocations();
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
	printf("\n");
#endif

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty()) {
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty()) {
			void* pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager->contains(pPtr) && pHeapManager->isAllocated(pPtr);
			assert(success);

			success = pHeapManager->free(pPtr);
			assert(success);
		}

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
		printf("After freeing allocations:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
		pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS

#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		pHeapManager->showOutstandingAllocations();
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		printf("\n");
#endif

		// do garbage collection
		pHeapManager->coalesce();
		// our heap should be one single block, all the memory it started with

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
		printf("After garbage collection:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
		pHeapManager->showFreeBlocks();
#endif // SUPPORTS_SHOWFREEBLOCKS

#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		pHeapManager->showOutstandingAllocations();
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		printf("\n");
#endif

		// do a large test allocation to see if garbage collection worked
		void* pPtr = pHeapManager->alloc(sizeHeap / 2);
		assert(pPtr);

		if (pPtr) {
			bool success = pHeapManager->contains(pPtr) && pHeapManager->isAllocated(pPtr);
			assert(success);

			success = pHeapManager->free(pPtr);
			assert(success);

		}
	}

	pHeapManager->destroy();
	pHeapManager = nullptr;

	DestroyHeapManager(pHeapManager);

	// we succeeded
	return true;
}
