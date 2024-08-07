/*
Two Sum

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.
*/

/*
Solution 1: Hash Table
1. Create a hash table to store the values and their corresponding indices from the array.
2. Iterate through the array. For each element, compute the difference between the target and the current element.
	If the difference is not in the hash table, store the current element as the key and its index as the value in the hash table.
	If the difference is found in the hash table, it means that the two numbers that add up to the target have been found. Retrieve the index of the difference from the hash table and the current index, and return both indices.
3. The algorithm terminates once the pair is found.

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> twosumHashTable(vector<int>& nums, int target) {
	unordered_map<int, int> hashtable;
	for (int i = 0; i < nums.size(); i++)
	{
		auto it = hashtable.find(target - nums[i]);
		if (it != hashtable.end()) {
			return { it->second,i };
		}
		hashtable[nums[i]] = i;
	}
	return {};
}


/*
Solution 2: Two Pointer
1. Sorting the array allows the use of the two-pointer technique effectively.
2. Utilize two pointers, one starting from the beginning (left) and one from the end (right) of the array.
3. Calculate the sum of the elements pointed to by the two pointers.
	If the sum equals the target, return the indices of these two elements.
	If the sum is less than the target, move the left pointer to the right to increase the sum.
	f the sum is greater than the target, move the right pointer to the left to decrease the sum.
4. Create a copy of the array that stores both the values and their original indices before sorting.
5. If a pair is found, return their original indices; if no such pair exists, return an empty array.

Time Complexity: O(nlogn)
Space Complexity: O(N)
*/

vector<vector<int>> twoSumTwoPointers(vector<int>& nums, int targe) {
	vector<vector<int>> results;
	vector<pair<int, int>> numsWithIndex;

	for (int i = 0; i < nums.size(); i++)
	{
		numsWithIndex.push_back({ nums[i],i });
	}

	sort(numsWithIndex.begin(), numsWithIndex.end());

	int left = 0;
	int right = numsWithIndex.size() - 1;

	while (left < right)
	{
		int sum = numsWithIndex[left].first + numsWithIndex[right].first;
		if (sum == targe)
		{
			results.push_back({ numsWithIndex[left].second,
				numsWithIndex[right].second });
			++left;
			--right;
		}
		else if (sum < targe) {
			++left;
		}
		else
		{
			--right;
		}
	}
	return results;
}


int mainTwoSum() {
	vector<int> nums = { 2, 7, 11, 15, -2, 3, 6 };
	int target = 9;
	vector<vector<int>> result = twoSumTwoPointers(nums, target);

	// Output the results
	if (!result.empty()) {
		for (const auto& pair : result) {
			cout << "Indices: " << pair[0] << ", " << pair[1] << endl;
		}
	}
	else {
		cout << "No solution found" << endl;
	}

	return 0;
}