#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
Maximum XOR of Two Numbers in an Array
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

1. Each number in the array is inserted into a Trie, with bits inserted from the most significant (31st) to the least significant (0th). Each node represents a bit: 0 to the left, 1 to the right.
2. For each number, the Trie is traversed to find another number that maximizes the XOR result. The search prioritizes paths with bits opposite to the current number's bit to maximize XOR. If such a path exists, it is chosen; otherwise, the available path is followed. If the opposite bit exists, the XOR value is left-shifted and 1 is appended; if not, the XOR value is left-shifted and the current bit is appended.
3. Trie allows efficient bitwise comparisons. The goal is to find paths in the Trie that differ as much as possible from the current number's path to maximize XOR. The algorithm starts from the highest bit to ensure significant contributions to the XOR result.

Time Complexity: O(n¡ÁL)
Space Complexity: O(n¡ÁL)
*/
struct TrieNode {
	TrieNode* children[2] = { nullptr,nullptr };
};

TrieNode* buildTrie(const vector<int>& nums) {
	TrieNode* root = new TrieNode();
	for (int num : nums) {
		TrieNode* node = root;
		for (int i = 31; i >= 0; i--) {
			int bit = (num >> i) & 1;
			if (node->children[bit] == nullptr) {
				node->children[bit] = new TrieNode();
			}
			node = node->children[bit];
		}
	}
	return root;
}

int findMaximumXOR(const vector<int>& nums) {
	TrieNode* root = buildTrie(nums);
	int max_xor = 0;
	for (int num : nums) {
		TrieNode* node = root;
		int current_xor = 0;
		for (int i = 31; i >= 0; --i) {
			int bit = (num >> i) & 1;
			if (node->children[1 - bit] != nullptr) {
				current_xor = (current_xor << 1) | 1;
				node = node->children[1 - bit];
			}
			else {
				current_xor = (current_xor << 1);
				node = node->children[bit];
			}
		}
		max_xor = max(max_xor, current_xor);
	}
	return max_xor;
}


int mainFindMaximumXOR() {
	vector<int> nums1 = { 3, 10, 5, 25, 2, 8 };
	vector<int> nums2 = { 14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70 };

	cout << "Maximum XOR of nums1: " << findMaximumXOR(nums1) << endl;
	cout << "Maximum XOR of nums2: " << findMaximumXOR(nums2) << endl;

	return 0;
}


/*
UTF-8 Validation

Given an integer array data representing the data, return whether it is a valid UTF-8 encoding. A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
1.For a 1-byte character, the first bit is a 0, followed by its Unicode code.
2.For an n-bytes character, the first n bits are all one's, the n + 1 bit is 0, followed by n - 1 bytes with the most significant 2 bits being 10.

1. Use a bitwise AND operation with a mask to identify the type of UTF-8 character (1-byte, 2-byte, 3-byte, or 4-byte).
2. Ensure that the array has enough remaining bytes to match the required length for the identified UTF-8 character type. If not, return false.
3. For the bytes following the first, use a bitwise AND operation with a mask to check if they conform to the 10xxxxxx pattern. If any byte doesn't match, return false.

Time Complexity: O(n)
Space Complexity: O(1)
*/
bool validUtf8(vector<int>& data) {
	int n = data.size();
	int i = 0;

	while (i < n) {
		int num_bytes = 0;

		switch (data[i] & 0b11111000) {
		case 0b11110000:  // 4-byte
			num_bytes = 4;
			break;
		case 0b11100000:  // 3-byte
			num_bytes = 3;
			break;
		case 0b11000000:  // 2-byte
			num_bytes = 2;
			break;
		case 0b00000000:  // 1-byte(ASCII)
			num_bytes = 1;
			break;
		default:
			return false;
		}

		if (i + num_bytes > n) {
			return false;
		}

		for (int j = 1; j < num_bytes; ++j) {
			if ((data[i + j] & 0b11000000) != 0b10000000) {
				return false;
			}
		}

		i += num_bytes;
	}

	return true;
}

int mainValidUtf8() {
	vector<int> test1 = { 197,130,1 };
	cout << "Test 1: " << (validUtf8(test1) ? "Valid" : "Invalid") << endl;

	vector<int> test2 = { 235,140,4 };
	cout << "Test 2: " << (validUtf8(test2) ? "Valid" : "Invalid") << endl;
	return 0;
}


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
