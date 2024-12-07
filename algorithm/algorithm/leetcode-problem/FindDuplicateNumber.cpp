#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

/*
Find the Duplicate Number
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive. There is only one repeated number in nums, return this repeated number. You must solve the problem without modifying the array nums and uses only constant extra space.

Approach 1: Binary Search
Approach 2: Floyd's (Tortoise and Hare/Cycle-Finding) Algorithm
1. Use two pointers, slow and fast. 'slow' moves one step at a time, while 'fast' moves two steps at a time. If there is a cycle, these two pointers will eventually meet. For example: 1 -> 2 -> 3 -> 4 -> 5 -> 3, there is a cycle.
2. Once the intersection is found, reset one pointer to the start of the array, and keep the other at the intersection point. Move both pointers one step at a time; the point where they meet is the entrance to the cycle, which is the duplicate number.

Time Complexity: O(N)
Space Complexity: O(1)

About:
1. When the slow and fast pointers first meet, it confirms that there is a cycle (or loop) within the structure, which, in this case, represents a duplicate element in the array. This first meeting point is somewhere inside the cycle, but not necessarily at the entry point of the cycle.
2. After the first encounter, the slow pointer is reset to the start of the array (nums[0]), while the fast pointer remains at the meeting point within the cycle. Both pointers then move one step at a time. Since the distance from the meeting point to the entry point of the cycle is equal to the distance from the start of the array to the entry point, the two pointers will inevitably meet at the cycle's entry point. This meeting point is the duplicate element being sought.
*/
int findDuplicate(vector<int>& nums) {
	int n = nums.size() - 1;

	for (int num : nums) {
		if (num<1 || num>n) {
			throw invalid_argument("Input array does not meet the problem's constraints.");
		}
	}

	int slow = nums[0];
	int fast = nums[0];

	// Finding the intersection point of two runners
	do
	{
		slow = nums[slow];
		fast = nums[nums[fast]];
	} while (slow != fast);

	// Finding the entrance to the cycle
	slow = nums[0];
	while (slow != fast)
	{
		slow = nums[slow];
		fast = nums[fast];
	}
	return slow;
}

int mainFindDuplicate() {
	vector<int> nums = { 3, 1, 3, 4, 2 };
	try {
		int duplicate = findDuplicate(nums);
		cout << "The duplicate number is: " << duplicate << endl;
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}
