#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;


/*
3 Sum Smaller
Given an array of n integers nums and an integer target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

Approach 1: Binary Search

Approach 2: Two-Pointer Method
1. After sorting the array, iterate through the array.
2. For each element in the array, select two other elements by initializing two pointers��one starting at the element immediately after the current element and the other at the end of the array.
3. If the sum of the three elements is less than the target, due to the sorted nature of the array, all elements between the two pointers satisfy the condition. Thus, the number of valid triplets can be quickly calculated by subtracting the indices of the two pointers. Then, move the left pointer (the one initialized at the next element) to the right.
4. If the sum is greater than or equal to the target, it means the condition is not satisfied, so the right pointer (the one initialized at the end of the array) is moved to the left.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
int threeSumSmaller(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());
	int count = 0;

	for (int i = 0; i < nums.size()-2; i++)
	{
		int j = i + 1;
		int k = nums.size() - 1;

		while (j < k) {
			if (nums[i] + nums[j] + nums[k] < target) {
				count += k - j;
				j++;
			}
			else
			{
				k--;
			}
		}
	}
	return count;
}

int mainThreeSumSmaller() {
	vector<int> nums = { -2, 0, 1, 3 };
	int target = 2;
	cout << "Number of triplets: " << threeSumSmaller(nums, target) << endl;

	return 0;
}


/*
Sum 3
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

1. Sort the input array nums.
2. Loop through the array with index i from 0 to (len(nums) - 3).
3. For each i, set two pointers: left at (i+1) and right at (len(nums) - 1).
4. Calculate the sum:
	If sum is equal to the target, add the triplet to the result.
	If sum is less than the target, move the left pointer to the right.
	If sum is more than the target, move the right pointer to the left.

Time Complexity: O(N^2)
Space Complexity: O(N^2)
*/

vector<vector<int>> threeSumTarget(vector<int>& nums, int target) {
	vector<vector<int>> result;

	sort(nums.begin(), nums.end());
	int n = nums.size();

	for (int i = 0; i < n - 2; i++) {
		int left = i + 1, right = n - 1;
		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];
			if (target == sum)
			{
				result.push_back({ nums[i] ,nums[left] ,nums[right] });
				// Avoid duplicates for the second element
				while (left < right && nums[left] == nums[left + 1]) {
					++left;
				}
				// Avoid duplicates for the third element
				while (left < right && nums[right] == nums[right - 1]) {
					--right;
				}
				++left;
				--right;
			}
			else if (target < sum) {
				++left;
			}
			else
			{
				--right;
			}

		}
	}
	return result;
}

/*
Sum 4
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

1. Sort the input array.
2. Loop through the array from 0 to 'len(nums) - 4'.
3. For each i, use another loop with index j from i+1 to 'len(nums - 3)'.
4. For each pari of i and j, set two pointers: left at j+1 and right at len(nums)-1.
5. Calculate the sum of 4 elements:
	If the sum is equal to the target, add the quadruplet to the result.
	If the sum is less than the target, move the left pointer to the right.
	If the sum is more than the target, move the right pointer to the left.

Time Complexity: O(N^3)
Space Complexity: O(N^2)
*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	int n = nums.size();

	for (int i = 0; i < n - 3; i++) {
		if (i > 0 && nums[i] == nums[i - 1])
			continue; // Avoid duplicates for the first element

		for (int j = i + 1; j < n - 2; j++) {
			if (j > i + 1 && nums[j] == nums[j - 1])
				continue; // Avoid duplicates for the second element
			int left = j + 1, right = n - 1;
			while (left < right)
			{
				int sum = nums[i] + nums[j] + nums[left] + nums[right];
				if (sum == target) {
					result.push_back({ nums[i], nums[j], nums[left], nums[right] });
					while (left < right && nums[left] == nums[left + 1])
					{
						++left;
					}
					while (left < right && nums[right] == nums[right - 1]) {
						--right;
					}
					++left;
					--right;
				}
				else if (sum < target)
				{
					++left;
				}
				else {
					--right;
				}
			}
		}
	}
	return result;
}


int main4Sum() {
	vector<int> nums = { 1, 0, -1, 0, -2, 2 };
	int target = 0;  // Example target value
	vector<vector<int>> result = fourSum(nums, target);

	for (const auto& quadruplet : result) {
		cout << "[";
		for (size_t i = 0; i < quadruplet.size(); ++i) {
			cout << quadruplet[i];
			if (i < quadruplet.size() - 1) cout << ", ";
		}
		cout << "]\n";
	}

	return 0;
}

int main3Sum() {
	vector<int> nums = { -1, 0, 1, 2, -1, -4 };
	int target = 0;
	vector<vector<int>> result = threeSumTarget(nums, target);

	for (const auto& triplet : result) {
		cout << "[";
		for (size_t i = 0; i < triplet.size(); ++i) {
			cout << triplet[i];
			if (i < triplet.size() - 1) cout << ", ";
		}
		cout << "]\n";
	}

	return 0;
}