#include <iostream>
#include <vector>

using namespace std;
/*
Kth Largest Element in an Array

Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
Can you solve it without sorting?

Quickselect Approach:
1. Rearrange the array so that elements less than or equal to the pivot are on the left and those greater are on the right. Returns the final position of the pivot.
2. Recursively find the k-th largest element by narrowing down the search space based on the pivot's position. Adjusts the search range until the k-th position is located.
*/
int partition(vector<int>& nums, int start, int end) {
	int pivotValue = nums[end];
	int smallerElementIndex = start;

	for (int i = start; i < end; i++)
	{
		if (nums[i] <= pivotValue) {
			swap(nums[i], nums[smallerElementIndex]);
			smallerElementIndex++;
		}
	}
	swap(nums[smallerElementIndex], nums[end]);
	return smallerElementIndex;
}

int quickSelect(vector<int>& nums, int left, int right, int k) {
	if (left == right) {
		return nums[left];
	}
	int pivotIndex = partition(nums, left, right);
	if (k == pivotIndex)
	{
		return nums[k];
	}
	else if (k < pivotIndex)
	{
		return quickSelect(nums, left, pivotIndex - 1, k);
	}
	else
	{
		return quickSelect(nums, pivotIndex + 1, right, k);
	}
}

int mainQuickSelect() {
	vector<int> nums = { 3, 2, 1, 5, 6, 4 };
	int k = 2, n = nums.size();
	int result = quickSelect(nums, 0, n - 1, n - k);
	cout << "The " << k << "th largest element is: " << result << endl;

	vector<int> nums2 = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };
	k = 4;
	n = nums2.size();
	result = quickSelect(nums2, 0, n - 1, n - k);
	cout << "The " << k << "th largest element is: " << result << endl;

	return 0;
}

