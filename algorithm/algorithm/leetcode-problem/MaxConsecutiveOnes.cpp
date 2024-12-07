/*
Max Consecutive Ones

Given a binary array nums, return the maximum number of consecutive 1's in the array.
*/

/*
1. Set 'int max = 0' to store the maximum number of consecutive 1's.Initialize a pointer start to 0.
2. Iterate through the array. When a 1 is encountered, if it's the first 1, record its index with start.
3. Continue until a 0 is encountered. When a 0 is found, calculate the length of consecutive 1s as 'i - start' and update max if this length is greater than the current max.
4. After encountering a 0, continue searching for the next 1. Record its index with start and repeat the process.
5. If the end of the array is reached while still in a sequence of 1s, calculate the length of this sequence as 'nums.size() - start' and update max if necessary.

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <vector>
#include <iostream>

using namespace std;

int findMaxConsecutiveOnes(vector<int>& nums) {
	int max = 0;
	int start = -1;

	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == 1) {
			if (start == -1)
			{
				start = i;
			}
		}
		else
		{
			if (start != -1)
			{
				max = std::max(max, i - start);
				start = -1;
			}
		}
	}
	if (start != -1) {
		max = std::max(max, (int)nums.size() - start);
	}
	return max;

}

int mainFindMaxConsecutiveOnes() {
	vector<int> nums1 = { 1, 1, 0, 1, 1, 1 };
	vector<int> nums2 = { 1, 0, 1, 1, 0, 1 };

	int result1 = findMaxConsecutiveOnes(nums1);
	int result2 = findMaxConsecutiveOnes(nums2);

	cout << "Test Case 1: " << result1 << endl; // Output should be 3
	cout << "Test Case 2: " << result2 << endl; // Output should be 2

	return 0;
}