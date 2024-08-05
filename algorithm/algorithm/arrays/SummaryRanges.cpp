/*
Summary Ranges

You are given a sorted unique integer array nums.

A range [a,b] is the set of all integers from a to b (inclusive).

Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.

Each range [a,b] in the list should be output as:

"a->b" if a != b
"a" if a == b
*/

/*
1. Set up two pointers, start and end. start points to the beginning of each interval to be output, initially set to 0. end is the index of the current element being traversed.

2. Iterate through the array and determine if the current element plus 1 is equal to the next element. This checks if two elements are consecutive. When the condition is triggered, either the current element is the last element in the array or the current element plus 1 is not equal to the next element, a discontinuity is found. At this point, output the interval defined by start and end, and then update start to (end + 1).

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> findSummaryRanges(vector<int>& nums) {
	vector<string> result;
	if (nums.empty()) return result;

	int start = 0;
	for (int end = 0; end < nums.size(); end++)
	{
		if (end + 1 == nums.size() || nums[end] + 1 != nums[end + 1]) {
			if (start == end) {
				result.push_back(to_string(nums[start]));
			}
			else
			{
				result.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
			}
			start = end + 1;
		}
	}
	return result;
}

int mainFindSummaryRanges() {
	
	vector<int> nums1 = { 0, 1, 2, 4, 5, 7 };
	vector<int> nums2 = { 0, 2, 3, 4, 6, 8, 9 };

	
	vector<string> result1 = findSummaryRanges(nums1);
	vector<string> result2 = findSummaryRanges(nums2);

	cout << "Test Case 1: ";
	for (const auto& range : result1) {
		cout << range << " ";
	}
	cout << endl;

	cout << "Test Case 2: ";
	for (const auto& range : result2) {
		cout << range << " ";
	}
	cout << endl;

	return 0;
}