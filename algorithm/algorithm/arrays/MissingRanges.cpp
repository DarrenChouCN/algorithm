/*
Missing Ranges

You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are within the inclusive range.

A number x is considered missing if x is in the range [lower, upper] and x is not in nums.

Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is, no element of nums is included in any of the ranges, and each missing number is covered by one of the ranges.
*/

/*
1. Use two variables, prev and cur, to record the left and right values of the range to be output. Since the result involves +1 or -1 of array elements, edge values need to be considered.
2. Define prev as lower - 1, and set the loop condition to i <= nums.size().
3. Start the loop, and when prev + 1 <= cur - 1, it indicates a missing range. Output this range, assign cur to prev, and continue the loop until the algorithm ends.

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
	vector<string> result;
	int prev = lower - 1;

	for (int i = 0; i <= nums.size(); i++)
	{
		int cur = i < nums.size() ? nums[i] : upper + 1;
		if (prev + 1 <= cur - 1) {
			result.push_back(to_string(prev + 1) + "->" + to_string(cur - 1));
		}
		prev = cur;
	}

	return result;
}

int mainFindMissingRanges() {
	vector<int> nums = { 0, 1, 3, 50, 75 };
	int lower = 0;
	int upper = 10;

	vector<string> missingRanges = findMissingRanges(nums, lower, upper);

	for (const string& range : missingRanges) {
		cout << range << " ";
	}

	return 0;
}