#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Product of Array Except Self
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i]. The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer. You must write an algorithm that runs in O(n) time and without using the division operation.

1. 'answer' array is initialized where 'answer[i]' stores the product of all elements to the left of nums[i].
2. Traverse the array from the left to right to fill the answer array with left products.
3. Traverse the array from right to left, calculating the right products and simultaneously updating the answer array to include the final result.

Time Complexity : O(n)
Space Complexity : O(1)
*/
vector<int> productExceptSelf(vector<int>& nums) {
	int n = nums.size();
	vector<int> answer(n, 1);

	for (int i = 1; i < n; i++)
	{
		answer[i] = answer[i - 1] * nums[i - 1];
	}

	int right_product = 1;
	for (int i = n-1; i >=0 ; i--)
	{
		answer[i] *= right_product;
		right_product *= nums[i];
	}

	return answer;
}

int mainProductExceptSelf() {
	vector<int> nums1 = { 1, 2, 3, 4 };
	vector<int> result1 = productExceptSelf(nums1);
	cout << "Output for [1, 2, 3, 4]: ";
	for (int num : result1) {
		cout << num << " ";
	}
	cout << endl;

	vector<int> nums2 = { -1, 1, 0, -3, 3 };
	vector<int> result2 = productExceptSelf(nums2);
	cout << "Output for [-1, 1, 0, -3, 3]: ";
	for (int num : result2) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}


/*
Subarray Sum Equals K

Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
A subarray is a contiguous non-empty sequence of elements within an array.

Cumulative Sum Approach
1. Initialize a hash map to store cumulative sums and their frequencies.
2. Initialize a variable to keep the cumulative sum and another to count the number of subarrays.
3. Iterate through the array, updating the cumulative sum and using the hash map to check and update the count of subarrays.

Time Complexity : O(n)
Space Complexity : O(n)
*/
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