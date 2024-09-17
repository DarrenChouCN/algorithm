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

## Detect Intersection of Two Singly Linked Lists
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

```cpp
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
```