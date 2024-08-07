/*
New Permutation

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).


1. Traverse the array from right to left to find the first element 'pivot' that is smaller than the element next to it.
2. Traverse the array from right to left to find the first element 'successor' that is larger than 'pivot'.
3. Swap the value of the pivot and the successor.
4. Reverse the sub-array that comes after the original index of the 'pivot' to get the next lexicographical permutation.

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void nextPermutation(vector<int>& nums) {
    int n = nums.size();

    int pivot = -1;
    for (int i = n - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
            pivot = i;
            break;
        }
    }

    if (pivot == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }

    for (int successor = n - 1; successor > pivot; --successor) {
        if (nums[successor] > nums[pivot]) {
            swap(nums[pivot], nums[successor]);
            break;
        }
    }
    reverse(nums.begin() + pivot + 1, nums.end());
}


int main() {
	vector<int> nums = { 1, 3, 5, 4, 2 };
	nextPermutation(nums);
	for (int num : nums) {
		cout << num << " ";
	}
	// Output: 1 4 2 3 5
	return 0;
}