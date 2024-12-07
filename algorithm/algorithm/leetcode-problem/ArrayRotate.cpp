#include <vector>
#include <iostream>

using namespace std;
/*
Rotate Array

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

1. Since rotating an array of length n by k steps is the same as rotating it by 'k%n' steps, first compute k=k%n to avoid unnecessary rotations.
2. Reverse the order of all elements in the array.
3. Place the first k elements in the correct order after the array rotation.
4. Restore the correct order for the remaining part of the array.

Time Complexity: O(n)
Space Complexity: O(1)
*/

void reverse(vector<int>& nums, int start, int end) {
	while (start < end)
	{
		swap(nums[start], nums[end]);
		start++;
		end--;
	}
}

void rotate(vector<int>& nums, int k) {
	int n = nums.size();
	k = k % n;
	reverse(nums, 0, n - 1);
	reverse(nums, 0, k - 1);
	reverse(nums, k, n - 1);
}

int mainRotateArray() {
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7 };
	int k = 3;
	rotate(nums, k);

	for (int num : nums) {
		cout << num << " ";
	}
	return 0;
}


/*
Rotate Image

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

1.The nested loops iterate through each element above the main diagonal and swap it with its corresponding element in the opposite position across the diagonal. This operation converts rows into columns.
2.The reverse() function is used to reverse the order of elements in each row of the matrix. This reordering gives the desired 90-degree clockwise rotation.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
void rotateImage(vector<vector<int>>& matrix) {
	int n = matrix.size();

	// Transpose the matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++) {
			swap(matrix[i][j], matrix[j][i]);
		}
	}

	// Reverse each row
	for (int i = 0; i < n; i++)
	{
		reverse(matrix[i].begin(), matrix[i].end());
	}
}


void testAndPrintRotate() {
	vector<vector<int>> matrix = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	cout << "Original matrix:" << endl;
	for (const auto& row : matrix) {
		for (int num : row) {
			cout << num << " ";
		}
		cout << endl;
	}
	cout << endl;

	rotateImage(matrix);

	cout << "Rotated matrix:" << endl;
	for (const auto& row : matrix) {
		for (int num : row) {
			cout << num << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int mainTestAndPrintRotate() {
	testAndPrintRotate();
	return 0;
}