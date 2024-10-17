#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> 

using namespace std;

/*
Monotonous Stack (No Repeats)
1. A stack is initialized to store the indices of the array elements. A 2D result array 'res' is initialized, where res[i][0] represents the index of the first element smaller than arr[i] on its left, and res[i][1] represents the index of the first element smaller than arr[i] on its right. If no such element exists, initialize with -1.
2. Traverse the array and for each element arr[i]: While the stack is not empty and the element at the top of the stack arr[stk.top()] is greater than arr[i], pop the top element. Then:
	Update the right boundary of the popped element with the current index i.
	Update the left boundary of the popped element with the next element in the stack. If the stack is empty, the left boundary remains -1.
	Push the current index into the stack if the stack top element is smaller than arr[i], maintaining the monotonic stack property.
3. After the traversal, any remaining elements in the stack have no smaller elements on their right. Set their right boundary to -1, while the left boundary remains as is or is updated.

Time and Space Complexity: O(n) and O(n)
*/
void processStack(stack<int>& stack, const vector<int> arr,
	vector<vector<int>>& result, int currentIndex, bool isFinal) {
	int rightIndex = isFinal ? -1 : currentIndex;
	while (!stack.empty() && (isFinal || arr[stack.top()] > arr[currentIndex])) {
		int topIndex = stack.top();
		stack.pop();
		int leftLessIndex = stack.empty() ? -1 : stack.top();
		result[topIndex][0] = leftLessIndex;
		result[topIndex][1] = rightIndex;
	}
}

vector<vector<int>> getNearLessNoRepeat(const vector<int>& arr) {
	int n = arr.size();
	stack<int> stack;
	vector<vector<int>> result(n, vector<int>(2, -1));

	for (int i = 0; i < n; i++)
	{
		processStack(stack, arr, result, i, false);
		stack.push(i);
	}

	processStack(stack, arr, result, -1, true);

	return result;
}

// Monotonous Stack with Duplicates  Time and Space Complexity: O(n) and O(n)
void processStackWithDuplicates(stack<vector<int>> stk, const vector<int>& arr,
	vector<vector<int>>& res, int currentIndex, bool isFinal) {
	int rightIndex = isFinal ? -1 : currentIndex;
	while (!stk.empty() && (isFinal || arr[stk.top().back()] > arr[currentIndex])) {
		vector<int> topList = stk.top();
		stk.pop();
		int leftLessIndex = stk.empty() ? -1 : stk.top().back();
		for (int index : topList) {
			res[index][0] = leftLessIndex;
			res[index][1] = rightIndex;
		}
	}
}

vector<vector<int>> getNearLessWithDuplicates(const vector<int>& arr) {
	int n = arr.size();
	stack<vector<int>> stk;
	vector<vector<int>> res(n, vector<int>(2, -1));

	for (int currentIndex = 0; currentIndex < n; currentIndex++)
	{
		processStackWithDuplicates(stk, arr, res, currentIndex, false);

		if (!stk.empty() && arr[stk.top().back()] == arr[currentIndex])
			stk.top().push_back(currentIndex);
		else
			stk.push({ currentIndex });
	}

	processStackWithDuplicates(stk, arr, res, -1, true);

	return res;
}


/*
Maximum Value of (Subarray Sum * Minimum Element)
Given an array 'arr' consisting of only positive integers, for any subarray 'sub', you can compute the value as (sum of sub) * (minimum element in sub). What is the maximum value of this expression over all possible subarrays?

1. calculate the prefix sum of the array for efficient subarray sum calculations.
2. Use a monotonic stack to process each element:
	i. If the element at the top of the stack is greater than or equal to the current element, it means a potential subarray has been found. Remove the element from the stack and compute the subarray sum from the left boundary (determined by the previous smaller element) to the current boundary. Multiply this sum by the minimum element of the subarray (which is the element being popped from the stack). Update the maximum value found so far.
	ii. If the element at the top of the stack is smaller than the current element, push the current element's index onto the stack.
3. After traversing the array, process any remaining elements in the stack using the same logic. Finally, return the maximum value found.

Time and Space Complexity: O(n) and O(n)
*/
int maxSubarrayValue(const vector<int>& arr) {
	int size = arr.size();

	vector<int> prefixSums(size);
	prefixSums[0] = arr[0];
	for (int i = 1; i < size; i++)
		prefixSums[i] = prefixSums[i - 1] + arr[i];

	stack<int> stk;
	int maxValue = INT_MIN;
	for (int i = 0; i < size; i++)
	{
		while (!stk.empty() && arr[stk.top()] >= arr[i]) {
			int minIndex = stk.top(); stk.pop();
			int sum = stk.empty() ?
				prefixSums[i - 1] : (prefixSums[i - 1] - prefixSums[stk.top()]);
			maxValue = max(maxValue, sum * arr[minIndex]);
		}
		stk.push(i);
	}

	while (!stk.empty()) {
		int minIndex = stk.top(); stk.pop();
		int sum = stk.empty() ?
			prefixSums[size - 1] : (prefixSums[size - 1] - prefixSums[stk.top()]);
		maxValue = max(maxValue, sum * arr[minIndex]);
	}

	return maxValue;
}

/*
Largest Rectangle in Histogram
Given an array of integers 'heights' representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Using an array to simulate a monotonic stack to solve this problem follows a similar approach to previous problems. Each time the top element of the stack is popped, the range between the popped index and the current element being traversed represents a possible solution. The width of the rectangle formed is i - widthStart - 1, and the height is determined by the height of the bar at the popped index (heights[minIndex]). The area is calculated as width * height, and the maximum value is updated accordingly. This approach ensures an efficient solution by handling all elements in a single pass with O(n) complexity.

Time and Space Complexity: O(n) and O(n)
*/
int largestRectangleArea(vector<int>& heights) {
	if (heights.empty()) return 0;

	int N = heights.size();
	vector<int> stack(N);
	int top = -1;
	int maxArea = 0;

	for (int i = 0; i < N; i++)
	{
		while (top != -1 && heights[stack[top]] >= heights[i]) {
			int heightIndex = stack[top--];
			int widthStart = (top == -1) ? -1 : stack[top];
			int currentArea = (i - 1 - widthStart) * heights[heightIndex];
			maxArea = max(maxArea, currentArea);
		}
		stack[++top] = i;
	}

	while (top != -1) {
		int heightIndex = stack[top--];
		int widthStart = (top == -1) ? -1 : stack[top];
		int currentArea = (N - widthStart - 1) * heights[heightIndex];
		maxArea = max(maxArea, currentArea);
	}

	return maxArea;
}


/*
Maximal Rectangle
Given a 'rows * cols' binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

The problem can be solved using a technique known as array compression. The idea is to treat each row of the 2D matrix as a base for constructing a histogram, where the height of each bar represents the count of consecutive 1's up to the current row. This will reduce the problem into multiple Largest Rectangle in Histogram subproblems, which can be solved efficiently using the same monotonic stack approach.

Traverse the matrix row by row, accumulating values from top to bottom. For each row, if an element is 0, reset the corresponding element in the new array to 0. The resulting array after each row can be treated as a "heights" array for the Largest Rectangle in Histogram problem. The solution can then be found using a monotonic stack.

Time and Space Complexity: O(n * m) and O(n)
*/
int maximalRectangle(vector<vector<char>>& matrix) {
	if (matrix.empty() || matrix[0].empty()) return 0;

	int maxArea = 0;
	int numCols = matrix[0].size();
	vector<int> height(numCols, 0);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < numCols; j++) {
			height[j] = (matrix[i][j] == '0') ? 0 : height[j] + 1;
		}
		maxArea = max(maxArea, largestRectangleArea(height));
	}

	return maxArea;
}


/*
Count Submatrices With All Ones
Given an m x n binary matrix mat, return the number of submatrices that have all ones.

1. Matrix Compression: Convert the matrix into a 1D array by compressing each row into heights. This transforms the problem into the Maximal Rectangle problem, allowing the use of the monotonic stack technique to solve it efficiently.
2. Monotonic Stack Processing:
	Step 1: Use a monotonic stack to process each region and compute the result for that region.
	Step 2: To avoid double-counting caused by equal heights leading to redundant calculations when popping from the stack, ensure that the condition 'if (height[cur] > height[i])' is used to exclude these cases.
	Step 3: Compute the width of the region, i.e., the distance between the current position and the left boundary. This is given by 'n = i - left - 1'.
	Step 4: Calculate the height of the region, which is the height difference between the current element and the left boundary, i.e., 'difference = height[cur] - height[left]'.
	Step 5: Count the number of subarrays where the current element is the minimum. The formula to calculate the number of subarrays is n * (n + 1) / 2, where n is the width of the region.
	Step 6: Accumulate the total area or count of submatrices that satisfy the conditions.

Time and Space Complexity: O(m*n) and O(n)
*/
int countFromBottom(const vector<int>& heights) {
	if (heights.empty()) return 0;

	int top = -1; // Stack pointer
	int nums = 0;
	int n = heights.size();
	vector<int> stack(n);

	for (int i = 0; i < n; i++)
	{
		while (top != -1 && heights[stack[top]] >= heights[i]) {
			int cur = stack[top--];
			if (heights[cur] > heights[i]) {
				int left = (top == -1) ? -1 : stack[top];
				int width = i - left - 1;
				int subarrayCount = (width * (width + 1)) / 2;

				int down = max((left == -1 ? 0 : heights[left]), heights[i]);
				int heightDifference = heights[cur] - down;

				nums += heightDifference * subarrayCount;
			}
		}
		stack[++top] = i;
	}

	while (top != -1) {
		int cur = stack[top--];

		int left = (top == -1) ? -1 : stack[top];
		int width = n - left - 1;
		int subarrayCount = (width * (width + 1)) / 2;

		int down = (left == -1) ? 0 : heights[left];
		int heightDifference = heights[cur] - down;

		nums += heightDifference * subarrayCount;
	}

	return nums;
}

int numSubmat(vector<vector<int>>& mat) {
	if (mat.empty() || mat[0].empty()) return 0;

	int nums = 0;
	vector<int> height(mat[0].size(), 0);

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++) {
			height[j] = (mat[i][j] == 0) ? 0 : height[j] + 1;
		}
		nums += countFromBottom(height);
	}

	return nums;
}

/*
Sum of Subarray Minimums
Given an array of integers arr, find the sum of 'min(b)', where 'b' ranges over every (contiguous) subarray of 'arr'. Since the answer may be large, return the answer modulo '10^9 + 7'.
*/
vector<int> nearLessEqualLeft(const vector<int>& arr) {
	int n = arr.size();
	vector<int> left(n);
	stack<int> s;

	for (int i = n - 1; i >= 0; i--)
	{
		while (!s.empty() && arr[s.top()] >= arr[i]) {
			left[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty()) {
		left[s.top()] = -1;
		s.pop();
	}

	return left;
}

vector<int> nearLessRight(const vector<int>& arr) {
	int n = arr.size();
	vector<int> right(n);
	stack<int> s;

	for (int i = 0; i < n; i++)
	{
		while (!s.empty() && arr[s.top()] > arr[i]) {
			right[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty()) {
		right[s.top()] = n;
		s.pop();
	}

	return right;
}

const int MOD = 1000000007;

int sumSubarrayMins(vector<int>& arr) {
	int n = arr.size();
	vector<int> left = nearLessEqualLeft(arr);
	vector<int> right = nearLessRight(arr);

	long long ans = 0;
	for (int i = 0; i < n; i++) {
		long long start = i - left[i];
		long long end = right[i] - i;
		ans = (ans + start * end * arr[i]) % MOD;
	}
	return (int)ans;
}

int main() {
	vector<int> arr = { 3, 1, 2, 4 }; // Example input
	cout << "Sum of Subarray Minimums: " << sumSubarrayMins(arr) << endl;
	return 0;
}