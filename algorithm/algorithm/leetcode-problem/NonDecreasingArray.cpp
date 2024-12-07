/*
Non-decreasing Array
Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.
We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).

1. Arrays of size 2 or less are always non-decreasing, return true.
2. Iterate through the array, checking if any element is greater than the next.
3. If such a case is found and no modification has been made yet, modify the array to maintain non-decreasing order. Decide whether to adjust the current element or the next based on surrounding values.
4. If a second modification is needed, return false. If the loop completes with at most one modification, return true.
*/
#include <vector>
using namespace std;

bool checkPossibility(vector<int>& nums) {
	int n = nums.size();
	bool modified = false;

	for (int i = 0; i < n - 1; ++i) {
		if (nums[i] > nums[i + 1]) {
			if (modified) return false;
			modified = true;
			// This will cause an out-of-bounds error when i == 0
			if (nums[i - 1] <= nums[i + 1]) {
				nums[i] = nums[i + 1];
			}
			else {
				nums[i + 1] = nums[i];
			}
		}
	}

	return true;
}