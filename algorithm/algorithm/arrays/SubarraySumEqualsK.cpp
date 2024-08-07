/*
Subarray Sum Equals K

Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
A subarray is a contiguous non-empty sequence of elements within an array.

Cumulative Sum Approach
1. Initialize a hash map to store cumulative sums and their frequencies.
2. Initialize a variable to keep the cumulative sum and another to count the number of subarrays.
3. Iterate through the array, updating the cumulative sum and using the hash map to check and update the count of subarrays.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int subarraySum(vector<int>& nums, int k) {
	int count = 0;
	int cumulativeSum = 0;
	unordered_map<int, int> cumulativeSumFreq;
	cumulativeSumFreq[0] = 1;

	for (int num : nums) {
		cumulativeSum += num;
		if (cumulativeSumFreq.find(cumulativeSum - k) != cumulativeSumFreq.end()) {
			count += cumulativeSumFreq[cumulativeSum - k];
		}
		cumulativeSumFreq[cumulativeSum]++;
	}
	return count;
}

int mainSubarraySum() {
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int k = 10;
	int result = subarraySum(nums, k);

	cout << "Number of subarrays with sum " << k << " is: " << result << endl;

	return 0;
}