#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Two-Pointer Method
1. The water volume is calculated unit by unit along the horizontal axis. The idea is to traverse the elevation map and, for each unit (or position), determine how much water can be stored above it.
2. Initialize two pointers, one at the start (left) and one at the end (right) of the array.
Traverse the array from both ends towards the center.
3. At each step, compare the heights at the left and right pointers.
	If the height at the left pointer is less than or equal to the height at the right pointer: Check if the height at the left pointer is less than the maximum height encountered so far on the left (left_max). If it is, water can be trapped above this bar, and the trapped water is left_max - height[left]. Move the left pointer one step to the right.
	If the height at the right pointer is less than the height at the left pointer: Check if the height at the right pointer is less than the maximum height encountered so far on the right (right_max). If it is, water can be trapped above this bar, and the trapped water is right_max - height[right]. Move the right pointer one step to the left.
4. Continue this process until the left and right pointers meet. The sum of all the calculated water volumes above each unit gives the total amount of water that can be trapped.

Time Complexity: O(n)
Space Complexity: O(1)
*/
int trap(const vector<int>& height) {
	if (height.empty())
		return 0;

	int left = 0, right = height.size() - 1;
	int leftMax = 0, rightMax = 0;
	int waterTrapped = 0;

	while (left < right) {
		if (height[left] <= height[right]) {
			if (leftMax > height[left])
				waterTrapped += leftMax - height[left];
			else
				leftMax = height[left];

			left++;
		}
		else
		{
			if (rightMax > height[right])
				waterTrapped += rightMax - height[right];
			else
				rightMax = height[right];

			right--;
		}
	}
	return waterTrapped;
}

int mainTrap() {
	vector<int> height1 = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	vector<int> height2 = { 4, 2, 0, 3, 2, 5 };
	vector<int> height3 = { 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };

	cout << "Test case 1: " << trap(height1) << " units of water trapped.\n";
	cout << "Test case 2: " << trap(height2) << " units of water trapped.\n";
	cout << "Test case 3: " << trap(height3) << " units of water trapped.\n";

	return 0;
}


/*
Container With Most Water

You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store.
Notice that you may not slant the container.

Two-pointer Approach
1. Start with two pointers, one at the beginning (left) and one at the end (right) of the array.
2. Compute the area formed between the two pointers as 'area = ((right-start) * min(height[left],height[right]))'.
3. Move the pointer which is at the shorter line inward, since the height of the container is limited by the shorter line.
4. Keep track of the maximum are found during the iteration.

Time Complexity: O(n)
Space Complexity: O(1)
*/
int maxArea(vector<int>& height) {

	int n = height.size();
	int left = 0, right = n - 1;
	int maxArea = 0;

	while (left < right)
	{
		int currentArea = (right - left) * min(height[left], height[right]);
		maxArea = max(currentArea, maxArea);

		if (height[left] < height[right]) left++;
		else right--;
	}

	return maxArea;
}

int mainMaxArea() {
	vector<vector<int>> test_cases = {
		{1, 8, 6, 2, 5, 4, 8, 3, 7},
		{1, 1},
		{4, 3, 2, 1, 4},
		{1, 2, 1},
		{2, 3, 10, 5, 7, 8, 9}
	};

	vector<int> expected_results = {
		49, 1, 16, 2, 36
	};

	for (int i = 0; i < test_cases.size(); ++i) {
		int result = maxArea(test_cases[i]);
		cout << "Test case " << result << endl;
	}

	return 0;
}