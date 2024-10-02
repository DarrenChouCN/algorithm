# Dynamic Programming

1. Recursion: The key to solving recursive problems is analyzing the branching structure. Each branch corresponds to a recursive call, with the parameters adjusted based on the problem¡¯s needs. After defining the branches and recursive function, constraints are added to prevent invalid or unnecessary recursion. Memoization can be used to further optimize the recursion process.
2. Memoization: Memoization is applied by introducing a storage structure alongside the existing recursion. This storage is used to check if a result has already been computed. If so, the stored result is used, bypassing the recursive call. Memoization reduces time complexity by trading off a certain amount of space.


## Hanoi Problem
The Tower of Hanoi is a mathematical puzzle consisting of three rods and n disks of different sizes. The puzzle starts with all the disks stacked in decreasing size order on the first rod (source). The objective is to move the entire stack to the third rod (destination), obeying the following rules:
1. Only one disk can be moved at a time.
2. A disk can only be moved if it is the uppermost disk on a rod.
3. No disk may be placed on top of a smaller disk.
Print all the steps to move n disks from the source rod to the destination rod using the middle rod (auxiliary) as an intermediary.

This problem can be understood as first using recursion to move the disks from the from rod to the aux rod. Due to the nature of a stack, the last disk to be placed on the auxiliary rod is the first one to be taken out. When these disks are transferred to the to rod following this rule, they are restored to their original order. This process is reflected in the code as recursive calls "return" layer by layer, progressively solving the problem.

Time and Space Complexity: O(2^n) and O(n)

```cpp
void hanoi(int n, char from, char to, char aux) {
	if (n == 1) {
		cout << "Move disk 1 from " << from << " to " << to << endl;
		return;
	}

	hanoi(n - 1, from, aux, to);

	cout << "Move disk " << n << "from" << from << " to " << to << endl;

	hanoi(n - 1, aux, to, from);
}
```

## Print All Subsequences of a String
Given a string, print all of its subsequences, including the empty string. A subsequence is a sequence derived from the original string by deleting some or no characters without changing the order of the remaining characters.

In a recursion tree, the root node represents the initial state. In each pair of parentheses, the value before the comma represents the part that has already been processed, while the value after the comma represents the part that remains to be processed. Moving to the left branch indicates that the first element is not processed (i.e., it is not added to the result), while moving to the right branch means that the first element is processed (i.e., it is added to the result). This operation repeats until the recursion terminates when there are no more elements to process.

```
Recursion tree:

			  ("", abc)

		 ("", bc)    ("a", bc)

	("", c)  ("b", c) ("a", c)  ("ab", c)

("", "") ("c", "") ("b", "") ("bc", "") ("a", "") ("ac", "") ("ab", "") ("abc", "")
```

Time and Space Complexity: O(2^n) and O(2^n)

```cpp
void subsequences(string str, int index, string current, vector<string>& result) {
	if (index == str.length()) {
		result.push_back(current);
		return;
	}

	subsequences(str, index + 1, current, result);

	subsequences(str, index + 1, current + str[index], result);
}
```


## Optimal Card Game
Given an array arr of integers, where each element represents a card with a unique value, the cards are laid out in a straight line. Two players, A and B, take turns picking cards. Player A always goes first, and Player B follows. Each player can only pick the card from either the leftmost or rightmost position in the array. Both players are extremely intelligent and will always make the best possible move to maximize their score. Return the score of the player who wins the game.

1. Dynamic Programming Tables (dpFirst and dpSecond): 'dpFirst' stores the optimal score for Player A in the range [left, right], while 'dpSecond' stores the optimal score for Player B in the same range. These tables are used to remember previously computed results for subproblems.
2. Avoiding Redundant Calculations: If a subproblem for the range [left, right] has already been computed (i.e., dpFirst[left][right] != -1 or dpSecond[left][right] != -1), the result is reused, avoiding unnecessary recursion.
3. Memoization: This optimization ensures each subproblem [left, right] is solved only once, and the result is stored in the DP table. This prevents recalculating the same subproblem multiple times, saving computational resources.

Time and Space Complexity: O(n^2) and O(n^2)

```cpp
int firstPlayerScore(const vector<int>& arr, int left, int right,
	vector<vector<int>>& dpFirst, vector<vector<int>>& dpSecond);

int secondPlayerScore(const vector<int>& arr, int left, int right,
	vector<vector<int>>& dpFirst, vector<vector<int>>& dpSecond);

int firstPlayerScore(const vector<int>& arr, int left, int right,
	vector<vector<int>>& dpFirst, vector<vector<int>>& dpSecond) {
	if (dpFirst[left][right] != -1)
		return dpFirst[left][right];

	if (left == right)
		return arr[left];

	dpFirst[left][right] = max(
		secondPlayerScore(arr, left + 1, right, dpFirst, dpSecond),
		secondPlayerScore(arr, left, right - 1, dpFirst, dpSecond)
	);

	return dpFirst[left][right];
}

int secondPlayerScore(const vector<int>& arr, int left, int right,
	vector<vector<int>>& dpFirst, vector<vector<int>>& dpSecond) {
	if (dpSecond[left][right] != -1)
		return dpSecond[left][right];

	if (left == right)
		return 0;

	dpSecond[left][right] = min(
		firstPlayerScore(arr, left + 1, right, dpFirst, dpSecond),
		firstPlayerScore(arr, left, right - 1, dpFirst, dpSecond)
	);

	return dpSecond[left][right];
}

int optimalCardGameScore(const vector<int>& arr) {
	int n = arr.size();

	vector<vector<int>> dpFirst(n, vector<int>(n, -1));
	vector<vector<int>> dpSecond(n, vector<int>(n, -1));

	return max(
		firstPlayerScore(arr, 0, n - 1, dpFirst, dpSecond),
		secondPlayerScore(arr, 0, n - 1, dpFirst, dpSecond)
	);
}
```

## Reverse a Stack
Given a stack of integers, write a function to reverse the stack using recursion. You cannot use any extra space other than the recursive call stack. The function should modify the stack in place.

The 'reverseStack' function recursively removes elements from the stack one by one until the stack is empty. The 'insertAtBottom' function is then used to insert each removed element back into the stack at the bottom. This process involves two recursive operations:
	1. The first recursion (reverseStack) removes all elements from the stack, storing them implicitly in the recursion stack.
	2. The second recursion (insertAtBottom) inserts each removed element back into the stack in reverse order during the recursion¡¯s unwinding phase.

Time and Space Complexity: O(n^2) and O(n)

```cpp
void insertAtBottom(stack<int>& stk, int value) {
	if (stk.empty()) {
		stk.push(value);
		return;
	}

	int topElement = stk.top();
	stk.pop();

	insertAtBottom(stk, value);

	stk.push(topElement);
}

void reverseStack(stack<int>& stk) {
	if (stk.empty()) return;

	int topElement = stk.top();
	stk.pop();

	reverseStack(stk);

	insertAtBottom(stk, topElement);
}
```

## Count the Number of Possible Decodings
Given a string of digits where '1' corresponds to 'A', '2' corresponds to 'B', and so on up to '26' corresponding to 'Z', write a function to return how many different possible decodings the string can have. For example, the string "111" can be decoded as "AAA", "KA", or "AK". The input string contains only numeric characters and does not contain leading zeros.

Time and Space Complexity: O(n) and O(n)

```cpp
int countDecodings(const string& s, int index, vector<int>& memo) {
	if (index = s.length())
		return 1;

	if (s[index] == '0')
		return 0;

	if (memo[index] != -1)
		return memo[index];

	int result = countDecodings(s, index + 1, memo);

	if (index + 1 < s.length()) {
		int twoDigit = stoi(s.substr(index, 2));
		if (twoDigit >= 10 && twoDigit <= 26) {
			result += countDecodings(s, index + 2, memo);
		}
	}

	memo[index] = result;

	return result;
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
```


## 0/1 Knapsack Problem
Given two arrays weights and values of length N, where the i-th position represents the weight and value of the i-th item, respectively. You are also given a positive integer bag, which represents the capacity of a knapsack. Your task is to determine the maximum value that can be obtained by selecting items such that the total weight does not exceed the capacity of the knapsack (bag). Each item can either be included in the knapsack or not.

Time and Space Complexity: O(n*bag) and O(n)

```cpp
int knapsack(const vector<int>& weights, const vector<int>& values,
	int i, int remainingBag, vector<vector<int>>& memo) {
	if (i == weights.size() || remainingBag == 0)
		return 0;

	if (memo[i][remainingBag] != -1) {
		return memo[i][remainingBag];
	}

	int withoutCurrentItem = knapsack(weights, values, i + 1, remainingBag, memo);

	int withCurrentItem = 0;
	if (weights[i] <= remainingBag) {
		withCurrentItem = values[i] + knapsack(
			weights, weights, i + 1, remainingBag - weights[i], memo);
	}

	memo[i][remainingBag] = max(withoutCurrentItem, withCurrentItem);
	return memo[i][remainingBag];
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
```

## Robot Movement
Given a linear path with N positions numbered from 1 to N (where N ¡Ý 2), a robot starts at position M (1 ¡Ü M ¡Ü N). The robot moves according to the following rules:
1. If the robot is at position 1, it can only move to position 2 in the next step.
2. If the robot is at position N, it can only move to position N-1 in the next step.
3. If the robot is at any position between 1 and N (i.e., 2 ¡Ü i ¡Ü N-1), it can move either left (to i-1) or right (to i+1) in the next step.

The robot must take exactly K steps, and you need to calculate how many distinct ways the robot can reach position P (1 ¡Ü P ¡Ü N) after K steps.
You are given four parameters:

	N: Total number of positions (N ¡Ý 2).
	M: Initial position of the robot (1 ¡Ü M ¡Ü N).
	K: Total number of steps the robot must take.
	P: Target position the robot needs to reach after K steps.

Return the total number of ways the robot can reach position P after exactly K steps.

```cpp
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

// Robot Movement (DP)
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
```

## Coin Change
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money. Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1. You may assume that you have an infinite number of each kind of coin.

Time and Space Complexity: O(n * amount) and O(n * amount)

```cpp
int coinChangeMemo(const vector<int>& coins, int index,
	int remaining, vector<vector<int>>& memo) {
	if (remaining == 0) 
		return 1;

	if (remaining < 0 || index == coins.size()) 
		return 0;

	if (memo[index][remaining] != -1)
		return memo[index][remaining];

	int includeCurrent = coinChangeMemo(coins, index, remaining - coins[index], memo);

	int excludeCurrent = coinChangeMemo(coins, index + 1, remaining, memo);

	memo[index][remaining] = includeCurrent + excludeCurrent;
	return memo[index][remaining];
}

int coinChange(const vector<int>& coins, int amount) {
	vector<vector<int>> memo(coins.size(), vector<int>(amount + 1, -1));

	return coinChangeMemo(coins, 0, amount, memo);
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
```

## Stickers to Spell Word
We are given n different types of stickers. Each sticker has a lowercase English word on it.
You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.

1. First, convert the given stickers and the target string into frequency arrays. The indices from 0 to 25 in the array correspond to the counts of the characters 'a' to 'z', respectively.
Recursion with Memoization:
2. Recursive Processing:
	a. In each recursive call, first check if the current state of the target string (represented by its frequency array) has already been computed (i.e., check if it exists in the memo map). If it does, directly return the stored result to avoid redundant calculations.
	b. If the frequency array targetCount is all zeros, it means all characters of the target string have been fully processed. In this case, return 0, indicating that no more stickers are needed.
	c. To determine the minimum number of stickers required, iterate through each sticker¡¯s frequency array. If a sticker does not contain any of the required target characters, skip this sticker. If a sticker contains target characters, use the sticker and update the target's frequency array, ensuring no frequencies go negative (i.e., don¡¯t reduce a character¡¯s count below zero).
3. Pass the updated target frequency array to the next recursive level and calculate the minimum number of stickers required for the remaining characters. After using a sticker, increment the sticker count by 1.
4. After iterating through all the stickers, select the solution that uses the fewest stickers by comparing the results. Store this minimum number of stickers in the memo map to avoid recalculating the same state in future recursive calls.

This problem can not use dynamic programming because the state space of this problem is too complex to define clear state transitions, and the dependency between subproblems is too strong due to the impact of different sticker choices on multiple characters and their order of application.

Time and Space Complexity: O(2^n) and O(T)
```cpp
vector<int> countCharFrequency(const string& str) {
	vector<int> freq(26, 0);
	for (char c : str)
		freq[c - 'a']++;
	return freq;
}

int minStickersRecursion(const vector<vector<int>>& stickerCounts,
	vector<int> targetCount, unordered_map<string, int> memo) {

	// Memorization
	string key;
	for (int c : targetCount)
		key += to_string(c) + ",";
	if (memo.count(key))
		return memo[key];

	// Base Key
	bool isEmpty = true;
	for (int count : targetCount) {
		if (count > 0) {
			isEmpty = false;
			break;
		}
	}
	if (isEmpty) return 0;

	// Recursion
	int minStickers = INT_MAX;
	for (const vector<int>& sticker : stickerCounts)
	{
		int index = -1;
		for (int i = 0; i < 26; i++) {
			if (targetCount[i] > 0) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			if (sticker[index] == 0) continue;
		}

		vector<int> newTargetCount = targetCount;
		for (int i = 0; i < 26; i++)
			newTargetCount[i] = max(0, newTargetCount[i] - sticker[i]);

		minStickers = min(minStickers,
			1 + minStickersRecursion(stickerCounts, newTargetCount, memo));
	}

	memo[key] = minStickers;
	return memo[key];
}

int minStickers(vector<string>& stickers, string target) {
	int n = stickers.size();
	vector<vector<int>> stickerCounts(n, vector<int>(26, 0));

	for (int i = 0; i < n; i++)
		stickerCounts[i] = countCharFrequency(stickers[i]);

	vector<int> targetCount = countCharFrequency(target);

	unordered_map<string, int> memo;

	int result = minStickersRecursion(stickerCounts, targetCount, memo);

	return result == INT_MAX ? -1 : result;
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
```

## Minimum Time to Complete All Cups
Given an array representing the time each person finishes drinking coffee and is ready to clean their cup. There is only one coffee machine, which can wash one cup at a time, and it takes a units of time to wash a cup. The machine can only start washing the next cup after the previous one is finished. Alternatively, each cup can dry by itself, which takes b units of time. Multiple cups can dry simultaneously.
Return the earliest time by which all the coffee cups can become clean (either by machine or drying).You are provided with three parameters:

	int[] arr: an array where each element represents the time a person finishes drinking coffee.
	int a: the time it takes for the machine to wash one cup.
	int b: the time it takes for a cup to dry naturally.

The goal is to calculate the minimum time to ensure all cups are clean.

Recursive Branches:

	Branch 1: The case of using the machine to wash the cup. The finish time for the current cup is the maximum of the cup's finish time and the machine's available time, plus the washing time.
	Branch 2: The case of natural drying. The finish time for the current cup is the sum of the cup's finish time and the drying time.
Recursively calculate all cases. Since the problem asks for the shortest time to clean all cups, the minimum of the results from Branch 1 and Branch 2 is chosen.

Time and Space Complexity: O(n) and O(n)

```cpp
int minCleanTimeRecursion(const vector<int>& drinkFinishTime, int curCup,
	int machineAvailableTime, int washTime, int dryTime) {
	if (curCup == drinkFinishTime.size()) return 0;

	int washFinishTime = max(drinkFinishTime[curCup], machineAvailableTime) + washTime;
	int cleanByMachine = minCleanTimeRecursion(drinkFinishTime, curCup + 1,
		washFinishTime, washTime, dryTime);
	washFinishTime = max(washFinishTime, cleanByMachine);

	int dryFinishTime = drinkFinishTime[curCup] + dryTime;
	int cleanByDry = minCleanTimeRecursion(drinkFinishTime, curCup + 1,
		machineAvailableTime, washTime, dryTime);
	dryFinishTime = max(dryFinishTime, cleanByDry);

	return min(washFinishTime, dryFinishTime);
}

int minCleanTime(const vector<int>& drinkFinishTime, int washTime, int dryTime) {
	return minCleanTimeRecursion(drinkFinishTime, 0, 0, washTime, dryTime);
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
```

## Longest Common Subsequence (LCS)
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence is a sequence that appears in the same relative order, but not necessarily consecutively. For example, "abc", "abg", "bdf", "aeg", "acefg", ... are subsequences of the string "abcdefg".

Recursive Branches:
	Branch 1: When the last elements are the same, increment the result by one and move both index pointers.
	Branch 2: When the last elements are different, use two recursive calls to compute the results by moving either one of the pointers forward.

Time and Space Complexity: O(2^min(m,n)) and O(m+n)
```cpp
int lcsRecursion(const string& text1, const string& text2, int i, int j) {
	if (i < 0 || j < 0) return 0;

	if (text1[i] == text2[j]) 
		return 1 + lcsRecursion(text1, text2, i - 1, j - 1);

	else 
		return max(lcsRecursion(text1, text2, i - 1, j), lcsRecursion(text1, text2, i, j - 1));
}

int lcs(const string& text1, const string& text2) {
	return lcsRecursion(text1, text2, text1.length() - 1, text2.length() - 1);
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
```