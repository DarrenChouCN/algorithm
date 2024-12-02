#include <set>
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
// Time and Space Complexity : O(N * sum) and O(N)
int maxDP1D(const vector<int>& arr, int m) {
	vector<bool> dp(m, false); // DP array to track reachable sums modulo m
	dp[0] = true;

	int maxModSum = 0;

	for (int num : arr) {
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


/*
When the values in the array 'arr' are very large and the modulus 'm' is relatively small, directly summing the elements may cause overflow. To address this, the 'dp' table in dynamic programming can be modified to have columns representing the remainder when each element is taken modulo 'm'. This modification allows tracking the remainder after taking modulo 'm', rather than the full sum, effectively preventing overflow and making state transitions more efficient.

In the implementation, dp[i][j] represents whether it is possible to form a remainder of j when considering the first i elements. During the state transition, the inclusion of the current element arr[i], with remainder cur = arr[i] % m, is considered. If j - cur or m + j - cur is a valid remainder state, then dp[i][j] can be set to true. This is because j - cur and m + j - cur represent undoing the contribution of the current element, with their positions also having a remainder of cur. Thus, the current state can be derived from the previous state, allowing for a direct update of the dp table.

Time and Space Complexity : O(N * m) and O(N * m)
*/
int maxDPWithLargeArr(const vector<int>& arr, int m) {
	int N = arr.size();

	// sum % m == j
	vector<vector<bool>> dp(N, vector<bool>(m, false));

	// sum % m == 0 is always achievable
	for (int i = 0; i < N; i++)
		dp[i][0] = true;

	dp[0][arr[0] % m] = true;

	for (int i = 1; i < N; i++) {
		int cur = arr[i] % m;
		for (int j = 0; j < m; j++) {
			// without current element
			dp[i][j] = dp[i - 1][j];

			if (j >= cur)
				dp[i][j] = dp[i][j] || dp[i - 1][j - cur];
			else
				dp[i][j] = dp[i][j] || dp[i - 1][m + j - cur];
		}
	}

	int ans = 0;
	for (int i = 0; i < m; i++)
		if (dp[N - 1][i])
			ans = i;
	return ans;
}

// Helper function to calculate all possible subset modulo sums for a given subarray
void calculateModuloSums(const vector<int>& arr,
	int index, int currentSum, int end, int m, set<int>& moduloSet) {
	if (index == end + 1)
		moduloSet.insert(currentSum % m);

	else {
		// Not including arr[index]
		calculateModuloSums(arr, index + 1, currentSum, end, m, moduloSet);

		// Including arr[index]
		calculateModuloSums(arr, index + 1, currentSum + arr[index], end, m, moduloSet);
	}
}


/*
When the values in the array arr and the modulus m are both large, the problem of directly summing elements and taking the modulo becomes computationally difficult. To solve this, a divide-and-conquer approach is used, splitting the array into two smaller subarrays. Each subarray is processed separately to compute all possible subset sums modulo m. The results are then combined by matching the sums from the left and right subarrays to maximize the total modulo sum. This approach avoids overflow and improves efficiency by reducing the problem size.

The array is divided into two parts, and each part calculates the possible subset sums modulo m using recursion. The results from both subarrays are stored in sorted sets. For each sum from the left subarray, the goal is to find the largest possible sum from the right subarray that, when combined with the left sum, does not exceed m. This is done using lower_bound to find the nearest valid sum from the right subarray. The maximum modulo sum is then calculated by combining the best possible sums from both subarrays.

Time and Space Complexity : O(2^N) and O(2^N)
*/
int maxDivedeAndConquer(const vector<int>& arr, int m) {
	int n = arr.size();
	if (n == 1) {
		return arr[0] % m;
	}

	int mid = (n - 1) / 2;
	set<int> leftModuloSet;
	calculateModuloSums(arr, 0, 0, mid, m, leftModuloSet);

	set<int> rightModuloSet;
	calculateModuloSums(arr, mid + 1, 0, n - 1, m, rightModuloSet);

	int maxModuloSum = 0;
	for (int leftMod : leftModuloSet) {
		// Find the smallest value >= m - leftMod
		auto it = rightModuloSet.lower_bound(m - leftMod);

		if (it != rightModuloSet.begin()) {
			--it; // Move one step back to get the largest valid mod <= m - leftMod
			maxModuloSum = max(maxModuloSum, (leftMod + *it) % m);
		}
	}
	return maxModuloSum;
}

int mainMax() {
	vector<int> arr = { 3, 3, 9, 9, 5 };
	int m = 7;
	cout << maxRecursion(arr, m) << endl;
	cout << maxDP2D(arr, m) << endl;
	cout << maxDP1D(arr, m) << endl;
	cout << maxDPWithLargeArr(arr, m) << endl;
	cout << maxDivedeAndConquer(arr, m) << endl;
	return 0;
}