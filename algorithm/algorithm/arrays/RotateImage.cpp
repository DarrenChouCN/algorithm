/*
Rotate Image

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

1.The nested loops iterate through each element above the main diagonal and swap it with its corresponding element in the opposite position across the diagonal. This operation converts rows into columns.
2.The reverse() function is used to reverse the order of elements in each row of the matrix. This reordering gives the desired 90-degree clockwise rotation.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
#include <vector>
#include <iostream>
using namespace std;

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