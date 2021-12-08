#include "TestQuestions.h"

#include <cassert>
#include <iostream>

// utility function that 
inline int RandInRange(int i_lowerBound, int i_upperBound) {
	assert(i_lowerBound < i_upperBound);

	return i_lowerBound + rand() % (i_upperBound - i_lowerBound);
}

void PrintList(LinkNode* root, int maxLength) {
	LinkNode* tmp = root;
	int count = 0;
	while (tmp != nullptr && count++ < maxLength) {
		std::cout << tmp->val << " -> ";
		tmp = tmp->next;
	}
	if (tmp == nullptr) std::cout << " NULL\n";
	else std::cout << "...???\n";
}

void DeleteList(LinkNode* root) {
	LinkNode* prev = root, *next = nullptr;
	while(prev != nullptr) {
		next = prev->next;
		delete prev;
		prev = next;
	}
}

/// <summary>
/// 1. Creates a random linked list and checks if it is circular.
///	2. Then forcefully makes it a circular list and checks if the new list has a cycle.
/// </summary>
void TestLinkedListHasCycle() {
	std::cout << "\n\nCreating a linked list of random numbers" << std::endl;
	int length = RandInRange(10, 15);
	LinkNode* root = new LinkNode(RandInRange(1, 100));
	LinkNode* prev = root;
	for(int i=1;i<length;i++) {
		prev->next = new LinkNode(RandInRange(1, 100));
		prev = prev->next;
	}
	PrintList(root, length);

	std::cout << std::boolalpha;
	bool isCircular = HasCycle(root);
	std::cout << "Is the above list circular?:: " << isCircular << std::endl;
	assert(!isCircular);

	std::cout << "Joining the tail to head..." << std::endl;
	prev->next = root;
	isCircular = HasCycle(root);
	std::cout << "Is the new list circular?:: " << isCircular << std::endl;
	assert(isCircular);
	prev->next = nullptr;

	// Clean Memory
	std::cout << "Assertions Successful\n" << std::endl;
	DeleteList(root);
}

/// <summary>
/// 1. Creates an array of random numbers with 0 and other numbers.
///	2. Tests if the zeros are rearranged
/// </summary>
void TestArrayOrderZeros() {
	std::cout << "\n\nCreating a array of random numbers with 0s "<< std::endl << "[";
	int length = RandInRange(10, 20);
	int* nums = new int[length];
	int zeroCount = 0;
	for (int i = 0; i < length; i++) {
		if (rand() & 1) { // 50% chance of completion
			nums[i] = 0;
			zeroCount++;
		} else {
			nums[i] = RandInRange(1, 100);
		}
		std::cout << nums[i] << " ";
	}
	std::cout << "]\n";
	ReorderZeros(nums, length);

	std::cout << "Array after reordering:\n[";
	for (int i = 0; i < length; i++) std::cout << nums[i] << " ";
	std::cout << "]\n";

	// Assertion
	for(int i=length-zeroCount;i<length;i++) {
		assert(nums[i] == 0);
	}
	std::cout << "Assertion Successful\n" << std::endl;
	delete[] nums;
}
