#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/*
General Thought Process for Dynamic Programming Design
When designing dynamic programming solutions, it is essential to start by calculating values that have already been determined (i.e., boundary values), and then proceed to compute the yet-to-be-determined values. While building the dynamic programming table, ensure that the traversal starts from the known elements and derives the unknown elements based on them.
1. Logical Consistency: Calculating from known to unknown values ensures the problem progression is natural and correct, avoiding index reversals and reducing errors.
2. Simplicity: Filling the DP table in a consistent manner keeps state dependencies clear, reducing complexity and simplifying implementation.
*/

// Optimal Card Game (DP)
int optimalCardGameScoreDP(const vector<int>& arr) {
	int n = arr.size();

	vector<vector<int>> dpFirst(n, vector<int>(n, 0));
	vector<vector<int>> dpSecond(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++)
	{
		dpFirst[i][i] = arr[i];
		dpSecond[i][i] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		int left = 0, right = i;
		while (left < n && right < n) {
			/*dpFirst[left][right] = max(
				secondPlayerScore(arr, left + 1, right, dpFirst, dpSecond),
				secondPlayerScore(arr, left, right - 1, dpFirst, dpSecond)
			);*/
			dpFirst[left][right] = max(arr[left] + dpSecond[left + 1][right],
				arr[right] + dpSecond[left][right - 1]);

			/*dpSecond[left][right] = min(
				firstPlayerScore(arr, left + 1, right, dpFirst, dpSecond),
				firstPlayerScore(arr, left, right - 1, dpFirst, dpSecond)
			);*/
			dpSecond[left][right] = min(dpFirst[left + 1][right],
				dpFirst[left][right - 1]);

			left++;
			right++;
		}
	}
	return dpFirst[0][n - 1];
}


// Count the Number of Possible Decodings (DP) Time and Space Complexity : O(n) and O(n)
int countDecodingsDP(const string& s) {
	int n = s.length();
	if (n == 0 || s[0] == '0')
		return 0;

	vector<int> dp(n + 1, 0);
	dp[n] = 1;

	for (int i = n - 1; i >= 0; i--)
	{
		// if (s[index] == '0') return 0;
		if (s[i] == '0') dp[i] = '0';
		else
		{
			//countDecodings(s, index + 1, memo);
			dp[i] = dp[i + 1];

			/*if (index + 1 < s.length()) {
				int twoDigit = stoi(s.substr(index, 2));
				if (twoDigit >= 10 && twoDigit <= 26) {
					result += countDecodings(s, index + 2, memo);
				}
			}*/
			if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
				dp[i] += dp[i + 2];
			}
		}
	}
	return dp[0];
}


// 0/1 Knapsack Problem (DP)  Time and Space Complexity : O(n*bag) and O(n*bag)
int knapsackDP(const vector<int>& weights, const vector<int>& values, int remainingBag) {
	int n = weights.size();
	vector<vector<int>> dp(n + 1, vector<int>(remainingBag + 1, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 1; j <= remainingBag; j++)
		{
			// knapsack(weights, values, i + 1, remainingBag);
			dp[i][j] = dp[i + 1][j];

			/*if (weights[i] <= remainingBag)
				values[i] + knapsack(weights, weights, i + 1, remainingBag - weights[i]);*/
			if (weights[i] <= j)
				dp[i][j] = max(dp[i][j], values[i] + dp[i + 1][j - weights[i]]);
		}
	}
	return dp[0][remainingBag];
}

// Robot Movement (DP)  Time and Space Complexity : O(K*N) and O(K*N)
int findWaysDP(int N, int M, int K, int P) {
	vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));

	dp[0][M] = 1;

	for (int k = 1; k <= K; k++)
		for (int i = 1; i <= N; i++) {
			if (i == 1)
				dp[k][i] = dp[k - 1][i + 1];
			else if (i == N)
				dp[k][i] = dp[k - 1][i - 1];
			else
				dp[k][i] = dp[k - 1][i - 1] + dp[k - 1][i + 1];
		}

	return dp[K][P];
}

// Coin Change  Time and Space Complexity : O(n*amount) and O(n*amount)
int coinChangeDP(const vector<int>& coins, int amount) {
	int n = coins.size();

	vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

	//if (remaining == 0) return 1;
	for (int i = 0; i <= n; i++) dp[i][0] = 1;

	for (int index = n - 1; index >= 0; index--)
	{
		for (int remaining = 0; remaining <= amount; remaining++) {
			//int excludeCurrent = coinChangeMemo(coins, index + 1, remaining, memo);
			dp[index][remaining] = dp[index + 1][remaining];

			//int includeCurrent = coinChangeMemo(coins, index, remaining - coins[index], memo);
			//memo[index][remaining] = includeCurrent + excludeCurrent;
			if (remaining >= coins[index]) {
				dp[index][remaining] += dp[index][remaining - coins[index]];
			}
		}
	}

	return dp[0][amount];
}

// Coin Change  Time and Space Complexity : O(n*amount) and O(amount)
int coinChangeDPWithLinearArray(const vector<int>& coins, int amount) {
	int n = coins.size();

	vector<int> dp(amount + 1, 0);
	dp[0] = 1;

	for (int coin : coins)
		for (int j = coin; j <= amount; j++)
			dp[j] += dp[j - coin];

	return dp[amount];
}

// Minimum Time to Complete All Cups  Time and Space Complexity: O(n * T) and O(n * T)
int minCleanTimeDP(const vector<int>& drinkFinishTime, int washTime, int dryTime) {
	int n = drinkFinishTime.size();

	int maxTime = *max_element(drinkFinishTime.begin(), drinkFinishTime.end()) + dryTime;
	vector<vector<int>> dp(n + 1, vector<int>(maxTime + 1, INT_MAX));

	//if (curCup == drinkFinishTime.size()) return 0;
	for (int j = 0; j <= maxTime; j++) dp[n][j] = 0;

	for (int i = n - 1; i >= 0; i--)
		for (int j = 0; j <= maxTime; j++) {
			/*int washFinishTime = max(drinkFinishTime[curCup], machineAvailableTime) + washTime;
			int cleanByMachine = minCleanTimeRecursion(drinkFinishTime, curCup + 1,
				washFinishTime, washTime, dryTime);
			washFinishTime = max(washFinishTime, cleanByMachine);*/
			int washFinishTime = max(drinkFinishTime[i], j) + washTime;
			if (washFinishTime <= maxTime) {
				washFinishTime = max(washFinishTime, dp[i + 1][washFinishTime]);
			}

			/*int dryFinishTime = drinkFinishTime[curCup] + dryTime;
			int cleanByDry = minCleanTimeRecursion(drinkFinishTime, curCup + 1,
				machineAvailableTime, washTime, dryTime);
			dryFinishTime = max(dryFinishTime, cleanByDry);*/
			int dryFinishTime = drinkFinishTime[i] + dryTime;
			dryFinishTime = max(dryFinishTime, dp[i + 1][j]);

			//return min(washFinishTime, dryFinishTime);
			dp[i][j] = min(washFinishTime, dryFinishTime);
		}

	return dp[0][0];
}

// Longest Common Subsequence (LCS)  Time and Space Complexity: O(n * m) and O(n * m)
int lcsDP(const string& text1, const string& text2) {
	int m = text1.length(), n = text2.length();

	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (text1[i - 1] == text2[j - 1])
				// return 1 + lcsRecursion(text1, text2, i - 1, j - 1);
				dp[i][j] = dp[i - 1][j - 1] + 1;

			else
				// return max(lcsRecursion(text1, text2, i - 1, j),
				// lcsRecursion(text1, text2, i, j - 1));
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

	return dp[m][n];
}

// Longest Palindromic Subsequence(LPS)  Time and Space Complexity: O(n^2) and O(n^2)
int lpsDP(string s) {
	int n = s.length();
	vector<vector<int>> dp(n, vector<int>(n, 0));

	//if (left == right) return 1;
	for (int i = 0; i < n; i++)
		dp[i][i] = 1;

	for (int left = n - 2; left >= 0; left--)
	{
		for (int right = left + 1; right < n; right++) {
			if (s[left] == s[right])
				//memo[left][right] = 2 + lpsRecursion(s, left + 1, right - 1, memo);
				dp[left][right] = 2 + dp[left + 1][right - 1];
			else
				/* memo[left][right] = max(
						lpsRecursion(s, left + 1, right, memo),
						lpsRecursion(s, left, right - 1, memo)
					);*/
				dp[left][right] = max(dp[left + 1][right], dp[left][right - 1]);
		}
	}
	return dp[0][n - 1];
}

// Knight's Moves on a Chessboard  Time and Space Complexity: O(9*10*k) and O(9*10*k)
int knightMovesDP[8][2] = {
	{1,2},{1,-2},{-1,2},{-1,-2},
	{2,1},{2,-1},{-2,1},{-2,-1}
};

int countKnightsMoveWaysDP(int x, int y, int k) {

	vector<vector<vector<int>>> dp(9, vector<vector<int>>(10, vector<int>(k + 1, 0)));
	dp[0][0][0] = 1;

	for (int step = 1; step <= k; step++)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				for (int m = 0; m < 8; m++) {
					int newX = i + knightMovesDP[m][0];
					int newY = j + knightMovesDP[m][1];
					if (newX >= 0 && newX < 9 && newY >= 0 && newY < 10) {
						dp[newX][newY][step] += dp[i][j][step - 1];
					}
				}

	return dp[x][y][k];
}