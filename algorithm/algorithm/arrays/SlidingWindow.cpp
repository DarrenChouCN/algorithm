#include <iostream>
#include <vector>

using namespace std;
/*
Maximum Average Subarray ¢ñ

You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.
*/

/*
Sliding Window Approach
1. First, calculate the sum of the first k elements. This sum represents the sum of the initial window.
2. Starting from the k-th element, slide the window one element at a time to the right. For each new element added to the window, update the window sum by subtracting the element that is left out from the window and adding the new element. This method efficiently updates the current window sum without recalculating the entire sum from scratch.
3. After each shift of the window, compare the current window sum to the maximum sum recorded so far. Update the maximum sum if the current window sum is greater.
4. After processing all possible windows, return the maximum sum divided by k to get the maximum average.

Time Complexity: O(N)
Space Complexity: O(1)
*/


double findMaxAverage(vector<int>& nums, int k) {
	double maxSum = 0;

	for (int i = 0; i < k; i++) {
		maxSum += nums[i];
	}

	double currentSum = maxSum;
	for (int i = k; i < nums.size(); i++)
	{
		currentSum += nums[i] - nums[i - k];
		maxSum = max(maxSum, currentSum);
	}

	return maxSum / k;
}

int mainFindMaxAverage() {
	vector<int> nums1 = { 1, 12, -5, -6, 50, 3 };
	int k1 = 4;
	cout << "Test Case 1: " << findMaxAverage(nums1, k1) << endl; // 12.75

	vector<int> nums2 = { 5, 5, 5, 5, 5, 5 };
	int k2 = 3;
	cout << "Test Case 2: " << findMaxAverage(nums2, k2) << endl; // 5.0

	return 0;
}

/*
Subarray Product Less Than K
Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

1. Use two pointer left and right to define a sliding window. Track the product of elements within thw window using product, and count valid subarrays with count.
2. Move right pointer across the array, multiplying product by nums[right]. If product>=k, shrink the window by moving left until product<k.
3. Each valid window contributes right-left+1 subarray. And the total count is returned.

Time Complexity: O(n)
Space Complexity: O(1)
*/

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
	if (k <= 1) return 0;
	int left = 0, count = 0, product = 1;

	for (int right = 0; right < nums.size(); right++)
	{
		product *= nums[right];
		while (product >= k)
		{
			product /= nums[left];
			left++;
		}

		count += right - left + 1;
	}

	return count;
}

int main() {
	vector<int> nums = { 10, 5, 2, 6 };
	int k = 100;

	int result = numSubarrayProductLessThanK(nums, k);

	cout << "The number of subarrays with product less than " << k << " is: " << result << endl;

	return 0;
}