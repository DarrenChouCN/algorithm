#include <iostream>
#include "common.h"

using namespace std;

/*
Palindrome Linked List
Determine if a singly linked list is a palindrome. You must solve this problem in O(1) extra space complexity and O(n) time complexity.

Fast and Slow Pointers:
1. Move the fast pointer two steps at a time and the slow pointer one step at a time. By the time the fast pointer reaches the end of the list, the slow pointer will reach the middle.
2. Once the slow pointer reaches the middle of the list, reverse the second half of the list.
3. Compare the values of the nodes from the start of the list with the nodes in the reversed second half. If all the values match, the linked list is a palindrome. If required, reverse the second half back to its original form.

Time and Space Complexity: O(n) and O(1)
*/
ListNode* reverseList(ListNode* head) {
	ListNode* prev = nullptr;
	while (head != nullptr) {
		ListNode* nextNode = head->next; // save the next node
		head->next = prev;
		prev = head; // move the prev pointer foward
		head = nextNode;
	}
	return prev;
}


bool isPalindrome(ListNode* head) {
	if (!head || !head->next) return true;

	ListNode* slow = head;
	ListNode* fast = head;

	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}

	// reverse the second half of the linked list
	ListNode* secondHalf = reverseList(slow);
	ListNode* firstHalf = head;

	// To restore the list later
	ListNode* secondHalfHead = secondHalf;

	while (secondHalf != nullptr) {
		if (firstHalf->val != secondHalf->val) {
			return false;
		}
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	reverseList(secondHalfHead);

	return true;
}