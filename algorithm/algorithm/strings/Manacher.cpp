#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

/*
Manacher's Algorithm
Manacher¡¯s algorithm is designed to find the longest palindromic substring in a given string in linear time. It transforms the input string and uses a central expansion approach with a symmetry property to efficiently compute the longest palindrome around each center.

1. pArr[i] represents the radius of the palindrome centered at position i. It allows us to skip unnecessary verification/comparison of characters. The palindrome radius for each position is calculated as follows:
	a. If i > rightBoundary: This means the current position i is outside the boundary of the known palindrome, so we must expand outward from this position to calculate the palindrome radius.
	b. If i <= rightBoundary: The current position i is within the right boundary, and we can utilize the symmetry property. The corresponding mirrored position i' (calculated as 2 * center - i) determines the palindrome's radius for i:
		If pArr[i'] is within the boundary of rightBoundary: The radius at i' is entirely within the bounds of rightBoundary, meaning pArr[i] = pArr[i'] as the palindrome radius is symmetric.
		If i is near the right boundary: The mirrored palindrome may extend beyond the boundary, so the palindrome radius of pArr[i] is limited to rightBoundary - i.
		If the palindrome at i' touches or exceeds the left boundary: The palindrome radius at i' is limited by the left boundary, and it can extend only within the limits of rightBoundary.

2. The calculation for i' is done using the formula pArr[2 * center - i], and the radius is determined by the smaller of pArr[i'] or the distance between i and the right boundary (rightBoundary - i).

3. After successfully calculating the initial palindrome radius, continue expanding outward to find a larger palindrome, checking if the new boundaries still match. If the palindrome extends symmetrically, increment the radius and repeat until the characters no longer match.

4. Update the center and rightBoundary when a new palindrome extends beyond the previous boundary (i + pArr[i] > rightBoundary), and keep track of the new center and right boundary positions.

5. Continuously track the maximum palindrome radius found during the iteration. Since the radius max includes the inserted characters (e.g., #), the actual palindrome length is max - 1.

Time and Space Complexity: O(n) and O(n)
*/
string preprocessString(const string& s) {
	vector<char> charArr(s.begin(), s.end());
	vector<char> res(s.length() * 2 + 1);
	int index = 0;
	for (int i = 0; i < res.size(); i++)
		res[i] = (i % 2 == 0) ? '#' : charArr[index++];

	return string(res.begin(), res.end());
}

int manacher(const string& s) {
	if (s.empty()) return 0;

	string str = preprocessString(s);
	int n = str.length();
	vector<int> pArr(n, 0);
	int center = -1;
	int rightBoundary = -1;
	int maxLength = INT_MIN;

	for (int i = 0; i < n; i++)
	{
		pArr[i] = i < rightBoundary ?
			min(pArr[2 * center - i], rightBoundary - i) : 1;

		while (i + pArr[i] < n && i - pArr[i] >= 0 && str[i + pArr[i]] == str[i - pArr[i]]) {
			pArr[i]++;
		}

		if (i + pArr[i] > rightBoundary) {
			rightBoundary = i + pArr[i];
			center = i;
		}

		maxLength = max(maxLength, pArr[i]);
	}

	return maxLength - 1;
}