#include <vector>
#include <iostream>

using namespace std;
/*
Single Number

Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Approach 1: Hash Map

Approach 2: Bit Manipulation
1. By performing XOR on all elements of the array, pairs of equal elements cancel each other out, leaving the XOR result of the two elements that appear only once.
2. From the XOR result, extract the lowest bit that is set to 1. This bit differentiates the two unique elements and helps in separating them.
3. By checking diffBit & current element, the elements can be divided into two groups. Those with diffBit set to 1 belong to one group, while those with diffBit set to 0 belong to another. Since diffBit is derived from the XOR of the two unique elements, these two elements will fall into different groups. Performing XOR within each group will isolate and identify the two elements that appear only once.

Time Complexity: O(N)
Space Complexity: O(1)
*/
vector<int> singleNumber(vector<int>& nums) {
	int xorResult = 0;

	//XOR all numbers to get the XOR of the two unique numbers
	for (int num : nums) {
		xorResult ^= num;
	}

	//Find a set bit (any bit that is 1) in xorResult
	int diffBit = xorResult & (-xorResult);

	//Separate numbers into two groups and XOR within each group
	int num1 = 0, num2 = 0;
	for (int num : nums) {
		if (num & diffBit) {
			num1 ^= num;
		}
		else {
			num2 ^= num;
		}
	}

	return { num1, num2 };
}

int mainSingleNumber() {
	vector<int> nums = { 1, 2, 1, 3, 2, 5 };
	vector<int> result = singleNumber(nums);
	cout << "The two unique numbers are: " << result[0] << " and " << result[1] << endl;
	return 0;
}
