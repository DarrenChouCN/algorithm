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

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

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