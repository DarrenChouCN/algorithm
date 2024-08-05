/*
Smallest Equal Index

Given a 0-indexed integer array nums, return the smallest index i such that i mod 10 == nums[i]. If no such index exists, return -1.
*/

/*
1. Start from the first element and check each element to see if i % 10 == nums[i].
2. If a matching index is found, return it immediately.
3. If no index satisfies the condition, return -1 after the loop completes.
*/

#include <iostream>
#include <vector>
using namespace std;

int smallestEqual(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        if (i % 10 == nums[i]) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> nums1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout << "Test Case 1: " << smallestEqual(nums1) << endl; // Should output 0

    vector<int> nums2 = { 4, 3, 2, 1, 0, 5, 6, 7, 8, 9 };
    cout << "Test Case 2: " << smallestEqual(nums2) << endl; // Should output 2

    vector<int> nums3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    cout << "Test Case 3: " << smallestEqual(nums3) << endl; // Should output -1

    return 0;
}