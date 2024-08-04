/*
Two Sum

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.
*/

/*
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
using namespace std;

class TwoSum {
public:
	vector<int> twosum(vector<int>& nums, int target) {
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
};

int main1() {
	auto printResult = [](vector<int> result) {
		if (!result.empty()) {
			cout << "Index:" << result[0] << "," << result[1] << endl;
		}else{
			cout << "No solution found." << endl;
		}
	};


	TwoSum twoSum;

	vector<int> nums1 = { 2,7,11,15 };
	vector<int> nums2 = { 3,2,4 };
	vector<int> nums3 = { 3,3 };

	int target1 = 9;
	int target2 = 6;
	int target3 = 5;

	vector<int> result1 = twoSum.twosum(nums1,target1);
	vector<int> result2 = twoSum.twosum(nums2,target2);
	vector<int> result3 = twoSum.twosum(nums3,target3);

	printResult(result1);
	printResult(result2);
	printResult(result3);

	return 0;
}