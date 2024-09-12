# Pointer Manipulation

## Palindrome Linked List
Determine if a singly linked list is a palindrome. You must solve this problem in O(1) extra space complexity and O(n) time complexity.

Fast and Slow Pointers:
1. Move the fast pointer two steps at a time and the slow pointer one step at a time. By the time the fast pointer reaches the end of the list, the slow pointer will reach the middle.
2. Once the slow pointer reaches the middle of the list, reverse the second half of the list.
3. Compare the values of the nodes from the start of the list with the nodes in the reversed second half. If all the values match, the linked list is a palindrome. If required, reverse the second half back to its original form.

```cpp
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
		if (firstHalf->value != secondHalf->value) {
			return false;
		}
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	reverseList(secondHalfHead);

	return true;
}
```

## Partition Linked List by Value
Given a singly linked list and a pivot value, rearrange the list such that all nodes with values less than the pivot appear before nodes with values equal to the pivot, and all nodes with values greater than the pivot appear after them. The relative order within the same group does not need to be maintained. The space complexity should be O(1), meaning no extra space for creating a new list is allowed.

Initializing the six pointers. Iterating through the linked list, classifying each node by updating the tail pointers for each section (less, equal, greater). Connecting the three lists. Returning the head of the new rearranged list.

Time and Space Complexity: O(n) and O(1)

```cpp
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
```

## Copy a Linked List with Random Pointer

Given a singly linked list where each node contains two pointers:
	next: Points to the next node in the list.
	random: Points to any node in the list or null.
You are required to copy the linked list with O(n) time complexity and O(1) space complexity.

1. For each node in the original list, a copied node is inserted right after it. This allows easy access to both the original and copied nodes.
2. The random pointers of the copied nodes are assigned by referencing the original node¡¯s random and its corresponding copied node.
3. The original and copied nodes are separated into two individual lists by adjusting the next pointers, restoring the original list and constructing the copied list.

Time and Space Complexity: O(n) and O(1)

```cpp
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
```