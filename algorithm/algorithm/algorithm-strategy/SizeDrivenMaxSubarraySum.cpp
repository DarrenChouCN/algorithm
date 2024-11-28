#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
/*
Maximum Subarray Sum Modulo m
Given a non-negative integer array 'arr' and a positive integer 'm', return the maximum value of the sum of any subarray of arr modulo m.

Constraints:
	1 <= arr.length <= 10^5
	1 <= arr[i] <= 10^9
	1 <= m <= 10^9
*/

// Brute Recursion
// Time and Space Complexity : O(2^n) and O(n)
void process(const vector<int>& arr, int index, int sum, unordered_set<int>& set) {
	if (index == arr.size())
		set.insert(sum);
	else {
		process(arr, index + 1, sum, set);

		process(arr, index + 1, sum + arr[index], set);
	}
}

int maxRecursion(const vector<int>& arr, int m) {
	unordered_set<int> set;
	process(arr, 0, 0, set);
	int maxMod = 0;

	for (int sum : set)
		maxMod = max(maxMod, sum % m);

	return maxMod;
}

// DP(2D)
// Time and Space Complexity : O(N * sum) and O(N * sum)
int maxDP2D(const vector<int>& arr, int m) {
	int sum = 0;
	int N = arr.size();

	for (int i = 0; i < N; i++)
		sum += arr[i];

	vector<vector<bool>> dp(N, vector<bool>(sum + 1, false));

	// Base case
	for (int i = 0; i < N; i++)
		dp[i][0] = true;

	dp[0][arr[0]] = true;
	for (int i = 1; i < N; i++)
		for (int j = 1; j <= sum; j++) {
			// Not including current element
			dp[i][j] = dp[i - 1][j]; 
			if (j - arr[i] >= 0) {
				// Including current element
				dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i]];
			}
		}

	int ans = 0;
	for (int j = 0; j <= sum; j++)
		if (dp[N - 1][j])
			ans = max(ans, j % m);

	return ans;
}


// DP(1D)
// Time and Space Complexity :
int maxDP1D(const vector<int>& arr, int m) {
	vector<bool> dp(m, false); // DP array to track reachable sums modulo m
	dp[0] = true;

	int maxModSum = 0;

	for (int num: arr) {
		vector<bool> newDp(dp);
		for (int j = 0; j < m; j++)
			if (dp[j]) {
				int newSum = (j + num) % m;
				newDp[newSum] = true;
				maxModSum = max(maxModSum, newSum);
			}
		dp = newDp;
	}

	return maxModSum;
}