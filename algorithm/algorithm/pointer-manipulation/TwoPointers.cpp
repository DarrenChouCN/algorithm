#include <iostream>
#include "../common.h"

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


/*
Detect Intersection of Two Singly Linked Lists
Given two singly linked lists that may or may not contain cycles, determine if they intersect. If they do, return the first intersection node; otherwise, return null. The time complexity should be O(n), and the space complexity should be O(1).

Detect if each list contains a cycle:
Use the fast and slow pointer method (Floyd's Cycle Detection Algorithm): The slow pointer moves one step at a time, while the fast pointer moves two steps at a time. If the list contains a cycle, the fast and slow pointers will eventually meet inside the cycle. If no cycle exists, the fast pointer will reach null. Once the pointers meet, move one of the pointers to the start of the list. Then move both pointers one step at a time. The point where they meet again is the cycle's entry node.

Handle different cases based on cycle detection:
1. Both lists have no cycle (null cycle entries):
	a. Traverse both lists to find their tail nodes. If the tail nodes are different, the lists do not intersect.
	b. If the tail nodes are the same, calculate the lengths of both lists. Move the pointer of the longer list ahead by the length difference. Then, move both pointers one step at a time. The point where they meet is the intersection node.
2. One list has a cycle, and the other does not:
	If one list contains a cycle while the other does not, the lists cannot intersect because a cycle prevents the list from reaching null. Therefore, return null.
3. Both lists contain cycles (non-null cycle entries):
	a. If the cycle entry nodes are the same, treat this entry as the effective end of both lists. Use the same length difference method as in the acyclic case to find the intersection point before the cycle or at the cycle entry.
	b. If the cycle entry nodes are different, traverse one of the lists starting from its cycle entry. If the traversal reaches the other list's cycle entry, the lists intersect. If no intersection occurs while traversing the cycle, the lists do not intersect.

Time and Space Complexity: O(n) and O(1)
*/

// Floyd's Cycle Detection Algorithm
ListNode* detectCycle(ListNode* head) {
	if (!head || !head->next) return nullptr;

	ListNode* slow = head, * fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			slow = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}
	return nullptr;
}

ListNode* getIntersectionWithoutCycle(ListNode* headA, ListNode* headB) {
	if (!headA || !headB) return nullptr;

	ListNode* tailA = headA;
	ListNode* tailB = headB;
	int lenA = 0, lenB = 0;

	while (tailA->next) {
		tailA = tailA->next;
		lenA++;
	}

	while (tailB->next) {
		tailB = tailB->next;
		lenB++;
	}

	if (tailA != tailB) return nullptr;

	ListNode* longer = lenA > lenB ? headA : headB;
	ListNode* shorter = lenA > lenB ? headB : headA;
	int diff = abs(lenA - lenB);

	while (diff--) longer = longer->next;

	while (longer && shorter && longer != shorter) {
		longer = longer->next;
		shorter = shorter->next;
	}

	return longer;
}

ListNode* getIntersectionWithCycle(ListNode* headA, ListNode* entryA,
	ListNode* headB, ListNode* entryB) {
	if (entryA != entryB) {
		ListNode* temp = entryA->next;
		while (temp != entryA) {
			if (temp == entryB)
				return entryA;
			temp = temp->next;
		}
	}

	else return getIntersectionWithoutCycle(headA, headB);

	return nullptr;
}

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
	if (!headA || !headB) return nullptr;

	ListNode* entryA = detectCycle(headA);
	ListNode* entryB = detectCycle(headB);

	if (!entryA && !entryB)
		return getIntersectionWithoutCycle(headA, headB);

	if ((entryA && !entryB) || (!entryA && entryB))
		return nullptr;

	return getIntersectionWithCycle(headA, entryA, headA, entryB);
}
