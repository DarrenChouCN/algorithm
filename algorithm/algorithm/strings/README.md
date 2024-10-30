# String Algorithms

## KMP (Knuth-Morris-Pratt) Algorithm

The KMP algorithm is used for pattern matching within a text. It efficiently searches for the occurrence of a "pattern" in a "text" by avoiding redundant comparisons. It builds a prefix table (partial match table) to skip unnecessary character comparisons, making it faster than the brute-force approach.

Generating the Prefix Function Array ��
1. Initialization: '��[0] = 0' because the first character has no prefix. The pointer 'prefixLen' is initially set to position 0, used to traverse the prefix area. The pointer 'i' starts traversing the string (pattern) from position 1.
2. Matching Process:
	a. If the match is successful, i.e., the elements at 'prefixLen' and 'i' positions are equal, then '��[i] = prefixLen + 1', and both pointers move one position to the right.
	b. If the match fails, then 'prefixLen = ��[prefixLen - 1]', meaning 'prefixLen' moves back to the start of the current prefix region (the range of each prefix region is from '��[prefixLen-1]' to 'prefixLen-1'). Continue comparing the element at position 'i' with the element at prefix. If there is still no match, 'prefixLen' is further adjusted according to the �� array, continuing to backtrack until 'prefixLen' reaches 0 or a matching prefix is found.
3. If 'prefixLen' reaches 0 and still doesn��t match, then set ��[i] = 0, and move 'i' to the next position. Continue until the array is fully traversed.

Time and Space Complexity:  O(n + m) and O(m)

```cpp
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
```

The logic of the KMP algorithm is similar to that of generating the prefix function array, as both compare characters in the pattern and use previously matched prefix information to backtrack when a mismatch occurs, avoiding restarting the comparison from the beginning. In both cases, the backtracking is based on the previously matched portion, using the prefix function array (�� array) to decide how to skip unnecessary comparisons.

The difference is that generating the prefix function array operates only on the pattern, recording the matching between its prefixes and suffixes, while the KMP algorithm uses the precomputed �� array to efficiently search for the pattern within a text, optimizing the matching process.

```cpp
vector<int> KMP1(const string& text, const string& pattern) {
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

bool KMP2(const string& text, const string& pattern) {
	vector<int> next = computePrefixFunction(pattern);
	int prefixLen = 0;

	for (int i = 0; i < text.length(); i++) {
		while (prefixLen > 0 && text[i] != pattern[prefixLen]) {
			prefixLen = next[prefixLen - 1];
		}
		if (text[i] == pattern[prefixLen]) {
			prefixLen++;
		}
		if (prefixLen == pattern.length()) {
			return true;
		}
	}
	return false;
}
```

## Rotate String Using KMP Algorithm
Given two strings s1 and s2, determine if s2 is a rotation of s1. A string rotation means moving characters from the beginning of the string to the end while preserving their order.

To determine if s2 is a rotation of s1, concatenate s1 with itself, effectively creating a string double the length of s1. Then use the KMP algorithm to check if s2 is a substring of the extended string. If it is, s2 is a rotation of s1; otherwise, it is not.

Time and Space Complexity:  O(n + m) and O(m)

```cpp
bool isRotation(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	string extendedS1 = s1 + s1;
	return KMP2(extendedS1, s2);
}
```

## Is Subtree Using KMP Algorithm
Given the roots of two binary trees, root and subRoot, determine if subRoot is a subtree of root. A subtree of a binary tree root is a tree consisting of a node in root and all of its descendants. The subtree can also be the entire tree root itself.

Serialize both trees into strings using a preorder traversal, and then use the KMP algorithm to compare them to determine whether one tree is a subtree of the other.

Time and Space Complexity:  O(n + m) and O(m)

```cpp
void serialize(TreeNode* root, string& res) {
	if (!root) {
		res += "# ";
		return;
	}
	res += to_string(root->val) + " ";
	serialize(root->left, res);
	serialize(root->right, res);
}

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
	string treeStr = "", subTreeStr = "";
	serialize(root, treeStr);
	serialize(subRoot, subTreeStr);

	return KMP2(treeStr, subTreeStr);
}
```

## Manacher's Algorithm
Manacher��s algorithm is designed to find the longest palindromic substring in a given string in linear time. It transforms the input string and uses a central expansion approach with a symmetry property to efficiently compute the longest palindrome around each center.

1. pArr[i] represents the radius of the palindrome centered at position i. It allows us to skip unnecessary verification/comparison of characters. The palindrome radius for each position is calculated as follows:
	a. If i > rightBoundary: This means the current position i is outside the boundary of the known palindrome, so we must expand outward from this position to calculate the palindrome radius.
	b. If i < = rightBoundary: The current position i is within the right boundary, and we can utilize the symmetry property. The corresponding mirrored position i' (calculated as 2 * center - i) determines the palindrome's radius for i:

		i. If pArr[i'] is within the boundary of rightBoundary: The radius at i' is entirely within the bounds of rightBoundary, meaning pArr[i] = pArr[i'] as the palindrome radius is symmetric.

		ii. If i is near the right boundary: The mirrored palindrome may extend beyond the boundary, so the palindrome radius of pArr[i] is limited to rightBoundary - i.

		iii. If the palindrome at i' touches or exceeds the left boundary: The palindrome radius at i' is limited by the left boundary, and it can extend only within the limits of rightBoundary.

2. The calculation for i' is done using the formula pArr[2 * center - i], and the radius is determined by the smaller of pArr[i'] or the distance between i and the right boundary (rightBoundary - i).

3. After successfully calculating the initial palindrome radius, continue expanding outward to find a larger palindrome, checking if the new boundaries still match. If the palindrome extends symmetrically, increment the radius and repeat until the characters no longer match.

4. Update the center and rightBoundary when a new palindrome extends beyond the previous boundary (i + pArr[i] > rightBoundary), and keep track of the new center and right boundary positions.

5. Continuously track the maximum palindrome radius found during the iteration. Since the radius max includes the inserted characters (e.g., #), the actual palindrome length is max - 1.

Time and Space Complexity: O(n) and O(n)

```cpp
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
```