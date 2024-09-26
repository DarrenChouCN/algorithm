#include <iostream>
#include <vector>

using namespace std;

/*
Robot Movement
Given a linear path with N positions numbered from 1 to N (where N ¡Ý 2), a robot starts at position M (1 ¡Ü M ¡Ü N). The robot moves according to the following rules:
If the robot is at position 1, it can only move to position 2 in the next step.
If the robot is at position N, it can only move to position N-1 in the next step.
If the robot is at any position between 1 and N (i.e., 2 ¡Ü i ¡Ü N-1), it can move either left (to i-1) or right (to i+1) in the next step.

The robot must take exactly K steps, and you need to calculate how many distinct ways the robot can reach position P (1 ¡Ü P ¡Ü N) after K steps.

You are given four parameters:
N: Total number of positions (N ¡Ý 2).
M: Initial position of the robot (1 ¡Ü M ¡Ü N).
K: Total number of steps the robot must take.
P: Target position the robot needs to reach after K steps.
Return the total number of ways the robot can reach position P after exactly K steps.
*/
int findWays(int N, int M, int K, int P, vector<vector<int>>& memo) {
	if (K == 0)
		return M == P ? 1 : 0;

	if (memo[K][M] != -1)
		return memo[K][M];

	int ways = 0;
	if (M == 1)
		ways = findWays(N, 2, K - 1, P, memo);

	else if (M == N)
		ways = findWays(N, N - 1, K - 1, P, memo);

	else
		ways = findWays(N, M - 1, K - 1, P, memo) + findWays(N, M + 1, K - 1, P, memo);

	memo[K][M] = ways;
	return ways;
}

int robotWays(int N, int M, int K, int P) {
	vector<vector<int>> memo(K + 1, vector<int>(N + 1, -1));
	return findWays(N, M, K, P, memo);
}

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