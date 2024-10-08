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

/*
Minimum Path Sum
In the original dynamic programming solution, a 2D table is used to store the minimum path sum for each cell. Since each cell only depends on the value to its left and the value above, the space complexity can be reduced from O(m * n) to O(n) by using a 1D array.
For each cell in subsequent rows, update dp[j] as the minimum of dp[j-1] (left) and dp[j] (above), plus the current cell value.

Time and Space Complexity: O(m * n) and O(n)
*/
int minPathSumDP(vector<vector<int>>& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	vector<int> dp(cols, 0);
	dp[0] = matrix[0][0];

	for (int j = 1; j < cols; j++)
		dp[j] = dp[j - 1] + matrix[0][j];

	for (int i = 1; i < rows; i++)
	{
		dp[0] += matrix[i][0];
		for (int j = 1; j < cols; j++)
			dp[j] = matrix[i][j] + min(dp[j], dp[j - 1]);
	}
	return dp[cols - 1];
}

// Bob's Survival Probability After k Moves 
// Time and Space Complexity: O(N * M * k * 4) and O(N * M * k)
int movesDP[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

double findProbabilityDP(int N, int M, int row, int col, int k) {

	vector<vector<vector<double>>> dp(N, vector<vector<double>>(M, vector<double>(k + 1, 0.0)));

	dp[row][col][k] = 1.0;

	for (int step = k; step > 0; step--)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (dp[i][j][step] > 0.0) {
					for (int m = 0; m < 4; m++) {
						int newRow = i + movesDP[m][0];
						int newCol = j + movesDP[m][1];

						if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M) {
							dp[newRow][newCol][step - 1] += dp[i][j][step] / 4.0;
						}
					}
				}

	// After processing all steps, sum the probabilities at step 0
	double result = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; ++j) {
			result += dp[i][j][0];
		}
	}
	return result;
}

// Kill Probability Time and Space Complexity: O(N * M * K) and O(N * K)
double killProbability(int N, int M, int K) {
	vector<vector<double>> dp(N + 1, vector<double>(K + 1, 0.0));

	for (int j = 0; j <= K; ++j)
		dp[0][j] = 1.0;

	for (int attack = 1; attack <= K; ++attack)
		for (int health = 0; health <= N; ++health)
			for (int damage = 0; damage <= M; ++damage) {
				int newHealth = health - damage;

				if (newHealth <= 0)
					dp[health][attack] += 1.0 / (M + 1);

				else
					dp[health][attack] += dp[newHealth][attack - 1] / (M + 1);
			}

	return dp[N][K];
}

// Min Coins  Time and Space Complexity: O(n * aim) and O(aim)
int minCoinsDP(int aim, const vector<int>& arr) {
	vector<int> dp(aim + 1, INT_MAX);
	dp[0] = 0;

	for (int i = 1; i <= aim; i++)
		for (int coin : arr)
			/*int res = minCoins(aim - coin, arr, memo);
			if (res != INT_MAX)
				minCoinsNeeded = min(minCoinsNeeded, res + 1);*/
			if (i >= coin && dp[i - coin] != INT_MAX) {
				dp[i] = min(dp[i], dp[i - coin] + 1);
			}
	return dp[aim] == INT_MAX ? -1 : dp[aim];
}

// Integer Partition with Decreasing Parts
int countPartitionsDP(int n) {
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

	for (int j = 0; j <= n; j++)
		dp[0][j] = 1;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			dp[i][j] = dp[i][j - 1];

			//result += countPartitions(n - k, k - 1, memo);
			if (i >= j) {
				dp[i][j] += dp[i - j][j - 1];
			}
		}

	return dp[n][n];
}

// Partition an Array into Two Subsets with Minimal Difference
// Time and Space Complexity: O(i * rest / 2) and O(i * rest / 2)
int closestSumDP(const vector<int> arr, int total) {
	int n = arr.size();
	int half = total / 2;

	vector<vector<int>> dp(n + 1, vector<int>(half + 1, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int rest = 0; rest <= half; rest++) {
			int excludeCurrent = dp[i + 1][rest];
			int includeCurrent = 0;
			if (arr[i] <= rest)
				includeCurrent = arr[i] + dp[i][rest - arr[i]];
			dp[i][rest] = max(excludeCurrent, includeCurrent);
		}
	}
	return dp[0][half];
}


// Partition Two Balanced Subsets with Minimal Difference
// Time and Space Complexity: O(n^2 * sum) and O(n^2 * sum)
int partitionBSDP(const vector<int>& arr) {
	if (arr.empty() || arr.size() < 2) return 0;

	
	int half = 0;
	for (int num : arr) half += num;
	half /= 2;
	int n = arr.size();
	int m = (n + 1) / 2;

	vector<vector<vector<int>>> dp(n + 1,
		vector<vector<int>>(m + 1, vector<int>(half + 1, -1)));

	/*if (i == arr.size())
		return picks == 0 ? 0 : -1;*/
	for (int rest = 0; rest <= half; rest++)
		dp[n][0][rest] = 0;

	for (int i = n - 1; i >= 0; i--)
		for (int picks = 0; picks <= m; picks++)
			for (int rest = 0; rest <= half; rest++) {
				int includeCurrent = dp[i + 1][picks][rest];

				int excludeCurrent = -1;
				int next = -1;
				if (picks >= 1 && arr[i] <= rest) {
					next = dp[i + 1][picks - 1][rest - arr[i]];
				}
				if (next != -1) {
					includeCurrent = arr[i] + next;
				}
				dp[i][picks][rest] = max(includeCurrent, excludeCurrent);
			}

	int evenResult = dp[0][n / 2][half];
	int oddResult = dp[0][n / 2 + 1][half];

	return n % 2 == 0 ? evenResult : max(evenResult, oddResult);
}