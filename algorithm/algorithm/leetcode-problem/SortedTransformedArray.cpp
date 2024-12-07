#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Sorted Transformed Array
Given a sorted integer array nums and three integers a, b and c, apply a quadratic function of the form f(x) = ax2 + bx + c to each element nums[i] in the array, and return the array in a sorted order.

1. Define two pointers at the start and end of the array and determine the filling direction of the result array based on the sign of a.
2. If a >= 0, the graph is an upward-opening parabola, with larger values at the ends and smaller values in the middle. Compare values at the pointers; place the larger value at the end of the result array, then move the corresponding pointer.
   If a < 0, the graph is a downward-opening parabola, with smaller values at the ends and larger values in the middle. Compare values at the pointers; place the smaller value at the beginning of the result array, then move the corresponding pointer.

Time Complexity: O(n)
Space Complexity: O(n)
*/
int calculate(int x, int a, int b, int c) {
    return a * x * x + b * x + c;
}

vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    int n = nums.size();
    vector<int> result(n);
    int left = 0, right = n - 1;
    // If a >= 0, fill from the end; otherwise, from the start
    int index = (a >= 0) ? n - 1 : 0;  

    while (left <= right) {
        int leftValue = calculate(nums[left], a, b, c);
        int rightValue = calculate(nums[right], a, b, c);

        if (a >= 0) {  // Fill from the end
            if (leftValue >= rightValue) {
                result[index--] = leftValue;
                left++;
            }
            else {
                result[index--] = rightValue;
                right--;
            }
        }
        else {  // Fill from the start
            if (leftValue <= rightValue) {
                result[index++] = leftValue;
                left++;
            }
            else {
                result[index++] = rightValue;
                right--;
            }
        }
    }

    return result;
}

int mainSortTransformedArray() {
    vector<int> nums = { -4, -2, 2, 4 };
    int a = 1, b = 3, c = 5;
    vector<int> result = sortTransformedArray(nums, a, b, c);

    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}