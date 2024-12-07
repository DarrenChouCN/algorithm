/*
Plus One

You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.
*/

/*
1. Start adding one from the last element of the array, so a pointer is needed to traverse the array from the end.
2. If the current element pointed to is not 9, increment this element by one and stop the traversal.
3. If the current element pointed to is 9, change it to 0 and move the pointer one position to the left. If the first element of the array is still 9 after the traversal, change it to 0 and add a 1 at the beginning of the array.

Time Complexity: O(N)
Space Complexity: O(1) or O(N)
*/

#include <vector>
#include <iostream>

using namespace std;

vector<int> plusOne(vector<int>& digits) {
	int n = digits.size();
	for (int i = n - 1; i >= 0; --i)
	{
		if (digits[i] != 9)
		{
			digits[i]++;
			return digits;
		}
		digits[i] = 0;
	}
	digits.insert(digits.begin(), 1);
	return digits;
}

int mainPlusOne() {

	vector<int> digits1 = { 9, 9, 9 };
	vector<int> digits2 = { 1, 2, 3 };

	vector<int> result1 = plusOne(digits1);
	vector<int> result2 = plusOne(digits2);

	cout << "Resulting array: ";
	for (int num : result2) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}