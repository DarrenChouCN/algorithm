#include <iostream>
#include "../common.h"

using namespace std;

/*
Partition Linked List by Value
Given a singly linked list and a pivot value, rearrange the list such that all nodes with values less than the pivot appear before nodes with values equal to the pivot, and all nodes with values greater than the pivot appear after them. The relative order within the same group does not need to be maintained. The space complexity should be O(1), meaning no extra space for creating a new list is allowed.

Initializing the six pointers. Iterating through the linked list, classifying each node by updating the tail pointers for each section (less, equal, greater). Connecting the three lists. Returning the head of the new rearranged list.

Time and Space Complexity: O(n) and O(1)
*/
ListNode* partition(ListNode* head, int pivot) {
	if (!head) return nullptr;

	ListNode* lessHead = nullptr, * lessTail = nullptr;
	ListNode* equalHead = nullptr, * equalTail = nullptr;
	ListNode* greaterHead = nullptr, * greaterTail = nullptr;

	ListNode* current = head;
	while (current) {
		ListNode* nextNode = current->next;
		current->next = nullptr;

		if (current->val < pivot) {
			if (!lessHead) lessHead = current;

			else lessHead->next = current;

			lessTail = current;
		}
		else if (current->val == pivot)
		{
			if (!equalHead) equalHead = current;

			else equalHead->next = current;

			equalTail = current;
		}
		else
		{
			if (!greaterHead) greaterHead = current;

			else greaterHead->next = current;

			greaterTail = current;
		}

		current = nextNode;
	}

	if (lessTail) lessTail->next = equalHead;
	if (equalTail) equalTail->next = greaterHead;

	// Determine the new head
	if (lessHead)
		return lessHead;

	else if (equalHead)
		return equalHead;

	else
		return greaterHead;
}

/*
Copy a Linked List with Random Pointer

Given a singly linked list where each node contains two pointers:
	next: Points to the next node in the list.
	random: Points to any node in the list or null.
You are required to copy the linked list with O(n) time complexity and O(1) space complexity.

1. For each node in the original list, a copied node is inserted right after it. This allows easy access to both the original and copied nodes.
2. The random pointers of the copied nodes are assigned by referencing the original node¡¯s random and its corresponding copied node.
3. The original and copied nodes are separated into two individual lists by adjusting the next pointers, restoring the original list and constructing the copied list.

Time and Space Complexity: O(n) and O(1)
*/
ListNode* copyRandomList(ListNode* head) {
	if (!head) return nullptr;

	// Insert copied nodes after each original node
	ListNode* current = head;
	while (current) {
		ListNode* newNode = new ListNode(current->val);
		newNode->next = current->next;
		current->next = newNode;
		current = newNode->next;
	}

	// set random pointers for copied nodes
	current = head;
	while (current) {
		if (current->random) {
			current->next->random = current->random->next;
		}
		current = current->next->next;
	}

	// seperate the original and copied lists
	current = head;
	ListNode* copyHead = head->next;
	ListNode* copyCurrent = copyHead;

	while (current) {
		current->next = current->next->next;
		if (copyCurrent->next) {
			copyCurrent->next = copyCurrent->next->next;
		}
		current = current->next;
		copyCurrent = copyCurrent->next;
	}

	return copyHead;
}