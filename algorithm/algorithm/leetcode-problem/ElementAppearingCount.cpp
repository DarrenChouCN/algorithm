/*
Element Appearing More than 25% in Sorted Array

Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.
*/

/*
1. Use a start pointer to record the first occurrence of an element.
2. Use an i pointer to iterate through the array until encountering an element different from nums[start].
3. Calculate the number of occurrences of the current element using (i - start).
4. If (i - start) / nums.size() is greater than 0.25, the current element is the target element.
5. Update start to the current element's position and continue traversing.

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <vector>
#include <iostream>

using namespace std;

int findSpecialInteger(vector<int>& nums) {
	int start = 0;
	int threshold = nums.size() / 4;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != nums[start]) {
			if (i - start > threshold) {
				return nums[start];
			}
			start = i;
		}
	}

	//If the element at the end of the array exceeds the threshold
	if (nums.size() - start > threshold) {
		return nums[start];
	}

	return -1;
}

int mainFindSpecialInteger() {
	vector<int> nums1 = { 1, 2, 2, 6, 6, 6, 6, 7, 10 };
	cout << "Test Case 1: " << findSpecialInteger(nums1) << endl; // Should output 6

	vector<int> nums2 = { 1, 1, 2, 2, 3, 3, 3, 3 };
	cout << "Test Case 2: " << findSpecialInteger(nums2) << endl; // Should output 3

	return 0;
}