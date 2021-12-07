#pragma once

struct LinkNode {
	int val;
	LinkNode* next;
	LinkNode(int x) : val(x), next(nullptr) {}
};

bool IsCircular(LinkNode* i_pRoot);
bool HasCycle(LinkNode* head);