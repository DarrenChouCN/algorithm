#include <vector>
#include <string>
#include <iostream>

using namespace std;

// KMP Algorithm  Time and Space Complexity:  O(n + m) and O(m)

/*
Generating the Prefix Function Array ¦Ð
1. Initialization: '¦Ð[0] = 0' because the first character has no prefix. The pointer 'prefixLen' is initially set to position 0, used to traverse the prefix area. The pointer 'i' starts traversing the string (pattern) from position 1.
2. Matching Process:
	a. If the match is successful, i.e., the elements at 'prefixLen' and 'i' positions are equal, then '¦Ð[i] = prefixLen + 1', and both pointers move one position to the right.
	b. If the match fails, then 'prefixLen = ¦Ð[prefixLen - 1]', meaning 'prefixLen' moves back to the start of the current prefix region (the range of each prefix region is from '¦Ð[prefixLen-1]' to 'prefixLen-1'). Continue comparing the element at position 'i' with the element at prefix. If there is still no match, 'prefixLen' is further adjusted according to the ¦Ð array, continuing to backtrack until 'prefixLen' reaches 0 or a matching prefix is found.
3. If 'prefixLen' reaches 0 and still doesn¡¯t match, then set ¦Ð[i] = 0, and move 'i' to the next position. Continue until the array is fully traversed.
*/
vector<int> computePrefixFunction(const string& pattern) {
	int n = pattern.length();
	vector<int> pi(n, 0);
	int prefixLen = 0;

	for (int i = 1; i < n; i++)
	{
		while (prefixLen > 0 && pattern[prefixLen] != pattern[i]) {
			prefixLen = pi[prefixLen - 1];
		}

		if (pattern[i] == pattern[prefixLen]) {
			prefixLen++;
		}

		pi[i] = prefixLen;
	}

	return pi;
}

/*
The logic of the KMP algorithm is similar to that of generating the prefix function array, as both compare characters in the pattern and use previously matched prefix information to backtrack when a mismatch occurs, avoiding restarting the comparison from the beginning. In both cases, the backtracking is based on the previously matched portion, using the prefix function array (¦Ð array) to decide how to skip unnecessary comparisons.

The difference is that generating the prefix function array operates only on the pattern, recording the matching between its prefixes and suffixes, while the KMP algorithm uses the precomputed ¦Ð array to efficiently search for the pattern within a text, optimizing the matching process.
*/
vector<int> KMP(const string& text, const string& pattern) {
	vector<int> pi = computePrefixFunction(pattern);
	vector<int> result;
	int prefixLen = 0;

	for (int i = 0; i < text.length(); i++)
	{
		while (prefixLen > 0 && text[i] != pattern[prefixLen]) {
			prefixLen = pi[prefixLen - 1];
		}

		if (text[i] == pattern[prefixLen]) {
			prefixLen++;
		}

		if (prefixLen == pattern.length()) {
			result.push_back(i - pattern.length() + 1);
			prefixLen = pi[prefixLen - 1];
		}

	}
	return result;
}