#ifndef COMMON_H
#define COMMON_H

struct ListNode
{
	int val;
	ListNode* next;
	ListNode* random;
	ListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

#endif // COMMON_H
