#include <vector>
#include <iostream>
#include <deque>

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