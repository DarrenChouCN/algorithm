/*
Find All Numbers Disappeared in an Array

Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
*/

/*
Solution 1 (Hash Table):
1. Initialize a hash table where each key represents a number from 1 to n, and the value represents the count of occurrences of that key. Initially, set all values to 0.
2. For each element in the given array, use it as a key in the hash table and increment its corresponding value by 1.
3. After traversing the array, go through the hash table and identify keys that have a value of 0. These keys represent the numbers that are missing from the original array.

Time Complexity: O(N)
Space Complexity: O(N)

Solution 2 (In-place Modification Method):
1. For each element 'nums[i]', use 'abs[nums[i]]-1' as the index 'index'. Set 'nums[index]' to a negative value to mark that the number 'index+1' has appeared in the array.
2. Identify all the positions 'i' that hold positive values. These positions correspond to the number 'i+1' that are missing from the original array.

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
	
	for (int i = 0; i < nums.size(); i++)
	{
		int index = abs(nums[i]) - 1;
		if (nums[index] > 0) {
			nums[index] = -nums[index];
		}
	}

	vector<int> result;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] > 0) {
			result.push_back(i + 1);
		}
	}
	return result;
}

int mainFindDisappearedNumbers() {
	vector<int> nums1 = { 4, 3, 2, 7, 8, 2, 3, 1 };
	vector<int> nums2 = { 1, 1 };

	vector<int> result1 = findDisappearedNumbers(nums1);
	vector<int> result2 = findDisappearedNumbers(nums2);

	// Print results
	cout << "Test Case 1: ";
	for (int num : result1) {
		cout << num << " ";
	}
	cout << endl;

	cout << "Test Case 2: ";
	for (int num : result2) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}

