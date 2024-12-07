#include <vector>
#include <unordered_map>

using namespace std;
/*
Majority Element

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Moore's Voting Algorithm
Moore's Voting Algorithm is designed to find elements that appear more than n/3 times in an array. It maintains two candidates and their counters, adjusting them as it traverses the array.

1. Initialize two candidates and their respective counters.
2. Traverse the array:
	If the current element matched one of the candidates, increment the corresponding counter.
	If the current element does not match either candidate: If a counter is zero, replace the corresponding candidate with the current element and set the counter to one; If both counters are non-zero, decrement both counters.
3. Traverse the array again to confirm whether the selected candidates appear more than n/3 times.
Time Complexity: O(n)
Space Complexity: O(1)

Risk:
1. If the threshold is reduced further (e.g. n/4, n/10), the effectiveness of the algorithm decreases, as more than two candidates may be required to accurately capture all elements meeting the new threshold.
2. The process of replacing candidates when their counters reach zero might cause valid candidates to be lost, potentially leading to inaccurate results if not carefully validated in the second pass.
*/
vector<int> majorityElement(vector<int>& nums) {
	int candidate1 = 0, candidate2 = 1, count1 = 0, count2 = 0;

	// First pass: find the candidates
	for (int num : nums) {
		if (num == candidate1) count1++;

		else if (num == candidate2) count2++;

		else if (count1 == 0) {
			candidate1 = num;
			count1 = 1;
		}

		else if (count2 == 0) {
			candidate2 = num;
			count2 = 1;
		}

		else {
			count1--;
			count2--;
		}
	}

	// Second pass: verify the candidates
	count1 = count2 = 0;
	for (int num : nums) {
		if (num == candidate1) count1++;
		else if (num == candidate2) count2++;
	}

	vector<int> result;
	int n = nums.size();
	if (count1 > n / 3) result.push_back(candidate1);
	if (count2 > n / 3) result.push_back(candidate2);

	return result;
}


/*
Hash Map Approach
1. Traverse the array and use a hash map to record the frequency of each element.
2. Iterate through the hash map to find elements that appear more than n/k times.
Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> majorityElementHashMap(vector<int>& nums, int k) {
	unordered_map<int, int> freq_map;
	vector<int> result;
	int n = nums.size();

	for (int num : nums)
	{
		freq_map[num]++;
	}
	for (auto& pair : freq_map)
	{
		int num = pair.first;
		int count = pair.second;
		if (count > n / k)
		{
			result.push_back(num);
		}
	}
	return result;
}
