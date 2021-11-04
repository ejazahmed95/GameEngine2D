#include "LinkedListProblems.h"

// Checks if the linked list is circular
bool IsCircular(LinkNode* i_pRoot) {
	LinkNode* temp = i_pRoot;
	while(temp!=nullptr) {
		temp = temp->next;
		if(temp == i_pRoot) {
			return true;
		}
	}
	return false;
}


// Checks if there is any cycle at all in the linked list
bool HasCycle(LinkNode* head) {
    LinkNode* temp = head;
    LinkNode* temp2 = head;
    while (temp2 != nullptr) {
        temp = temp->next;
        temp2 = temp2->next;
        if (temp2 == nullptr) break;
        temp2 = temp2->next;
        if (temp == temp2) return true;
    }
    return false;
}
