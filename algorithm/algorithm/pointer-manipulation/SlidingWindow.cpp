#include <vector>
#include <iostream>
#include <deque>
#include <queue>

using namespace std;

/*
In sliding window problems, a LinkedList or deque is used to maintain a monotonic queue, either in decreasing or increasing order, based on the requirements.
1. Decreasing sequence: When a new element enters the window, it is compared with the elements at the back of the deque. If the new element is greater than or equal to the back elements, the back elements are removed since they cannot be the maximum in future windows. This continues until the correct position is found, and the new element is added to the back. After each window slide, the front element is checked and removed if it moves out of the window. The maximum value remains at the front of the deque.
2. Increasing sequence: For an increasing sequence, back elements that are greater than or equal to the new element are removed. This ensures the minimum value remains at the front.
*/

/*
Sliding Window Maximum
Given an array and a fixed-size sliding window W, return the maximum value for each sliding window.
Content: Assume a fixed-size window W slides over the array arr, and for each sliding step, return the maximum value within the window.

Since this problem requires finding the maximum value within each sliding window of width and returning an array, the result array length will be array.size() - w + 1. Following the principle of maintaining a sliding window using a deque, the front of the deque will always store the maximum value for the current window. As the window moves forward, the element at the front is removed and added to the result array, continuing until the entire array is processed.

Time and Space Complexity: O(n) and O(w)
*/
vector<int> getMaxWindow(vector<int>& arr, int width) {
	if (arr.empty() || width < 1 || arr.size() < width) return {};

	vector<int> result(arr.size() - width + 1);

	deque<int> qmax;
	int index = 0;

	for (int right = 0; right < arr.size(); right++) {
		while (!qmax.empty() && arr[qmax.back()] <= arr[right]) {
			qmax.pop_back();
		}

		qmax.push_back(right);

		// Remove the element that's out of the window from the front
		if (qmax.front() == right - width) {
			qmax.pop_front();
		}

		// Form the window and stores the current window maximum value
		if (right >= width - 1) {
			result[index++] = arr[qmax.front()];
		}
	}
	return result;
}


/*
Number of Subarrays with Bounded Maximum-Minimum Difference
Given an integer array 'arr' and an integer 'num', determine how many subarrays of 'arr' satisfy the following condition :
The difference between the maximum value and the minimum value in the subarray 'sub' is less than or equal to 'num'.

Assume the range of values in an array is [min,max]. For any subarray within this range, its maximum value will be less than or equal to max, and its minimum value will be greater than or equal to min. To efficiently manage subarrays, a sliding window can be maintained using two pointers, along with two deques: one for tracking the maximum values and one for tracking the minimum values in the current window.

Following the sliding window principle:
Each time a new element enters the window, it is added to both deques (for maximum and minimum values).
The difference between the elements at the front of the two deques (representing the maximum and minimum values of the current window) is checked.
	1. If the difference is less than or equal to num, the current window satisfies the condition, and the right boundary of the window moves further to expand it.
	2. If the difference is greater than num, a valid subarray has been found, and the left boundary is moved to shrink the window.
The difference between the right and left boundaries gives the number of valid subarrays, which is added to the total result. The deques are updated (removing elements from the front) as the window slides.

Time and Space Complexity: O(n) and O(w)
*/
int numSubarraysWithDifference(vector<int>& arr, int sum) {
	if (arr.empty() || sum < 0) return 0;

	int N = arr.size();
	int count = 0;
	deque<int> maxWindow, minWindow;

	int right = 0;
	for (int left = 0; left < N; left++) {
		while (right < N) {
			if (!maxWindow.empty() && arr[maxWindow.back()] <= arr[right]) {
				maxWindow.pop_back();
			}
			maxWindow.push_back(right);

			if (!minWindow.empty() && arr[minWindow.back()] >= arr[right]) {
				minWindow.pop_back();
			}
			minWindow.push_back(right);

			if (arr[maxWindow.front()] - arr[minWindow.front()] > sum) break;

			else right++;
		}

		count += right - left;

		if (maxWindow.front() == left)
			maxWindow.pop_front();

		if (minWindow.front() == left)
			minWindow.pop_front();
	}

	return count;
}

/*
Gas Station
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.
Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique.

The task is to identify a starting point from which it is possible to travel around the entire circular array without running out of gas at any station. The array is expanded to a linear structure by doubling its length.

1. diff[i] stores the cumulative net gas from the starting point up to index i. The array is extended to a length of 2N to simulate the circular nature. The prefix sum allows for efficient calculation of any subarray's cumulative sum to determine if there is enough gas to travel from a starting point to an endpoint.
2. A sliding window approach is applied, where left and right denote the boundaries of the window, and offset represents the cumulative sum up to the left boundary. The expression diff[window.front()] - offset calculates the difference between the minimum prefix sum within the window and the cumulative sum before the starting point. A non-negative result indicates that starting from left satisfies the condition.

The sliding window moves across the array, evaluating each potential starting point. The window maintains the minimum prefix sum, and the difference between this value and offset determines if the net gas is sufficient to complete a full circuit from that point.

Time and Space Complexity: O(n) and O(n)
*/
vector<bool> canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int N = gas.size();
	int M = N * 2;
	vector<bool> result(N, false);

	// Create a new array arr based on gas and cost differences
	vector<int> diff(M, 0);
	for (int i = 0; i < N; i++)
	{
		diff[i] = gas[i] - cost[i];
		// Extend array to handle circular route
		diff[i + N] = gas[i] - cost[i];
	}

	// Calculate cumulative sum in the array to handle sum-based sliding window
	for (int i = 1; i < M; i++)
		diff[i] += diff[i - 1];

	// First pass to fill the deque with the first N elements
	deque<int> window;
	for (int i = 0; i < N; i++)
	{
		while (!window.empty() && diff[window.back()] >= diff[i])
			window.pop_back();

		window.push_back(i);
	}

	int offset = 0;
	// Sliding window over the second half of the array
	for (int left = 0, right = N; right < M; left++, right++) {
		offset = diff[left];

		// Check if the current window meets the condition
		if (diff[window.front()] - offset >= 0)
			result[left] = true;

		// Remove elements that are out of the window's left boundary
		if (window.front() == left)
			window.pop_front();

		// Maintain the sliding window
		while (!window.empty() && diff[window.back()] >= diff[right]) {
			window.pop_back();
		}
		window.push_back(right);
	}

	return result;
}

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

int mainMedianSlidingWindow() {
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