#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

/*
Find the leftmost position in a sorted array where the element is greater than or equal to a given target.

Time Complexity: O(logn)
Space Complexity: O(1)
*/
int binarySearchLeftMost(vector<int>& arr, int target) {
	int left = 0, right = arr.size() - 1;
	int result = -1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] >= target) {
			result = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return result;
}


/*
Find Peak Element
A peak element is an element that is strictly greater than its neighbors.
Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks. You must write an algorithm that runs in O(log n) time.

Find the middle element. Decide which half contains the peak and adjust left and right to narrow the search. Finally, left will point to a peak element.

Time Complexity: O(logn)
Space Complexity: O(1)
*/
int findPeakElement(vector<int>& nums) {
	int left = 0, right = nums.size() - 1;

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (nums[mid] > nums[mid + 1]) {
			right = mid; // Peak is on the left side
		}
		else {
			left = mid + 1; // Peak is on the right side
		}
	}

	return left; // left points to a peak element
}


/*
Find Minimum in Rotated Sorted Array
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
Given the sorted rotated array nums of unique elements, return the minimum element of this array. You must write an algorithm that runs in O(log n) time.

1. Since the array is partially sorted, binary search is an optimal approach.
2. If the middle element 'mid' is greater than the rightmost element 'right', the minimum must be in the right half. If the middle element is less than or equal to the rightmost element, the minimum is in the left half, including possibly 'mid'.
3. If nums[mid]>nums[right], move the left boundary to mid+1. Otherwise, move the right boundary to mid.
4. The search terminates when the left pointer converges with the right, pointing to the minimum element.

Time Complexity: O(logn)
Space Complexity: O(1)
*/
int findMin(vector<int>& nums) {
	int left = 0, right = nums.size() - 1;

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (nums[mid] > nums[right]) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	return nums[left];
}


/*
Find fisrt and last position of element is sorted array

Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].
You must write an algorithm with O(log n) runtime complexity.

1. First Binary Search: The objective is to find the starting position of the target element.The comparison uses 'nums[mid] >= target'.
2. Second Binary Search: The objective is to find the ending position of the target element. The comparison uses 'nums[mid] <= target'.

Time Complexity: O(logn)
Space Complexity: O(1)
*/
vector<int> searchRange(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	int first = -1, last = -1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] >= target) {
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
		if (nums[mid] == target)
			first = mid;
	}

	left = 0;
	right = nums.size() - 1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] <= target) {
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
		if (nums[mid] == target)
			last = mid;
	}

	return { first,last };
}

void testSearchRange() {
	std::vector<int> nums1 = { 5, 7, 7, 8, 8, 10 };
	std::vector<int> result1 = searchRange(nums1, 8);
	assert(result1 == std::vector<int>({ 3, 4 }));

	std::vector<int> nums2 = { 5, 7, 7, 8, 8, 10 };
	std::vector<int> result2 = searchRange(nums2, 6);
	assert(result2 == std::vector<int>({ -1, -1 }));

	std::vector<int> nums3 = {};
	std::vector<int> result3 = searchRange(nums3, 0);
	assert(result3 == std::vector<int>({ -1, -1 }));

	std::vector<int> nums4 = { 1, 1, 1, 1, 1 };
	std::vector<int> result4 = searchRange(nums4, 1);
	assert(result4 == std::vector<int>({ 0, 4 }));

	std::vector<int> nums5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> result5 = searchRange(nums5, 7);
	assert(result5 == std::vector<int>({ 6, 6 }));

	std::cout << "All test cases passed!" << std::endl;
}

int mainTestSearchRange() {
	testSearchRange();
	return 0;
}


/*
Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.

Binary Search Approach
1. Set two pointers, left at the beginning and right at the end of the array.
2. Binary Search Loop:
	Calculate the middle index mid and check if the middle element is target. If yes return mid.
	Determine which half of the array is sorted:
		If the left half is sorted (nums[left]<=nums[mid]), check if the target lies within the sorted left half (nums[left]<=target<=nums[mid]). If yes, move the right pointer to 'mid-1'; Otherwise, move the left pointer to 'mid+1';
		If the right half is sorted (nums[mid]<=nums[right]), check if the target lies within the sorted right half (nums[mid]<target<=nums[right]). If yes, move the left pointer to 'mid+1'; Otherwise, move the right pointer to 'mid-1';
	If the target is found, return its indesx. If the loop ends without finding the target, return -1;

Time Complexity: O(logn)
Space Complexity: O(1)
*/

int searchInRotatedArray(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {

		int mid = left + (right - left) / 2;
		if (nums[mid] == target)
		{
			return mid;
		}
		if (nums[left] <= nums[mid]) {
			if (nums[left] <= target && target < nums[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		else {
			if (nums[mid] < target && target <= nums[right])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
	}
	return -1;
}


int mainSearchInRotatedArray() {
	vector<int> nums1 = { 4, 5, 6, 7, 0, 1, 2 };
	int target1 = 0;
	cout << "Test case 1: " << searchInRotatedArray(nums1, target1) << endl;

	vector<int> nums2 = { 4, 5, 6, 7, 0, 1, 2 };
	int target2 = 3;
	cout << "Test case 2: " << searchInRotatedArray(nums2, target2) << endl;

	vector<int> nums3 = { 1 };
	int target3 = 0;
	cout << "Test case 3: " << searchInRotatedArray(nums3, target3) << endl;

	return 0;
}