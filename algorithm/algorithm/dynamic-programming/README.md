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
```