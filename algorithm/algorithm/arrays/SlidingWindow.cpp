#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Sliding Window Median
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.

1. Use two heaps to efficiently find the median: Max-Heap for the smaller half of the window; Min-Heap for the larger half. The Max-Heap is initialized first, as the design assumes the Max-Heap will have either the same number or one more element than the Min-Heap. This helps ensure that the median is easily accessible from the heap tops.
2. As the window slides, insert the new element into the appropriate heap (Max-Heap or Min-Heap) and remove the outgoing element. After each insertion/removal, rebalance the heaps to maintain the condition that the Max-Heap has at most one more element than the Min-Heap.
3. The median is chosen from the larger heap¡¯s top element: If the heaps are balanced, the median is the average of the tops of both heaps. If the Max-Heap has more elements, the median is the top of the Max-Heap. This is because, in a sorted sequence, the median is either the middle element or the average of the two middle elements, with the Max-Heap representing the "left half" of the sorted window.

About:
1. The dual heap structure ensures the median (the middle element) is always at the top of one or both heaps, making retrieval efficient.
2. Typically, heaps are implemented using dynamic arrays (e.g., std::priority_queue in C++), automatically maintaining heap properties with each insertion or deletion.

Time Complexity: O(nlogk)
Space Complexity: O(k)
*/
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
	vector<double> result;
	priority_queue<int> max_heap;
	priority_queue<int, vector<int>, greater<int>> min_heap;

	for (int i = 0; i < nums.size(); i++)
	{
		// Insert into appropriate heap
		if (max_heap.empty() || nums[i] <= max_heap.top()) {
			max_heap.push(nums[i]);
		}
		else
		{
			min_heap.push(nums[i]);
		}

		// Rebalance the heaps if necessary
		if (max_heap.size() > min_heap.size() + 1) {
			min_heap.push(max_heap.top());
			max_heap.pop();
		}
		else if (min_heap.size() > max_heap.size()) {
			max_heap.push(min_heap.top());
			min_heap.pop();
		}

		// window has been formed, calculate the median
		if (i >= k - 1) {
			if (max_heap.size() == min_heap.size()) {
				result.push_back(((double)max_heap.top() + min_heap.top()) / 2.0);
			}
			else
			{
				result.push_back((double)max_heap.top());
			}

			// Remove the element that is sliding out of the window
			int element_to_remove = nums[i - k + 1];
			if (element_to_remove <= max_heap.top()) {
				max_heap.pop();
			}
			else
			{
				min_heap.pop();
			}

			// Rebalance the heaps if necessary
			if (max_heap.size() > min_heap.size() + 1) {
				min_heap.push(max_heap.top());
				max_heap.pop();
			}
			else if (min_heap.size() > max_heap.size()) {
				max_heap.push(min_heap.top());
				min_heap.pop();
			}
		}
	}

	return result;
}

int main() {
	vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
	int k = 3;

	vector<double> result = medianSlidingWindow(nums, k);

	cout << "Sliding window medians are: ";
	for (double median : result) {
		cout << median << " ";
	}
	cout << endl;

	return 0;
}



/*
Minimum Size Subarray Sum
Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

1. Start with two pointers left and right both pointing to the beginning of the array.
2. Move the right pointer to expand the window, adding the current element to the cumulative sum.
3. Whenever the sum is greater than or equal to the target, move the left pointer to shrink the window while updating the minimal length of the subarray.
4. Repeat the above steps until the right pointer reaches the end of the array.

Time Complexity: O(N)
Space Complexity: O(1)
*/
int minSubArrayLen(int target, vector<int>& nums) {
	int left = 0, sum = 0, minLength = INT_MAX;

	for (int right = 0; right < nums.size(); right++)
	{
		sum += nums[right];

		while (sum >= target)
		{
			minLength = min(minLength, right - left + 1);
			sum -= nums[left];
			left++;
		}
	}
	return minLength == INT_MAX ? 0 : minLength;
}

int mainMinSubArrayLen() {
	vector<int> nums = { 2, 3, 1, 2, 4, 3 };
	int target = 7;

	int result = minSubArrayLen(target, nums);
	cout << "The minimum length of a subarray with a sum >= " << target << " is: " << result << endl;

	return 0;
}

/*
Maximum Average Subarray ¢ñ

You are given an integer array nums consisting of n elements, and an integer k. Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

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

int mainNumSubarrayProductLessThanK() {
	vector<int> nums = { 10, 5, 2, 6 };
	int k = 100;

	int result = numSubarrayProductLessThanK(nums, k);

	cout << "The number of subarrays with product less than " << k << " is: " << result << endl;

	return 0;
}