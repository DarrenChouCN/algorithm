#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Minimum Bags to Pack Apples
You are given two types of plastic bags from a store, each with unlimited availability:
A bag that can hold 6 apples.
A bag that can hold 8 apples.
You need to use these two types of bags to pack apples such that:
Every bag is completely full. The total number of bags used is minimized.
Given a positive integer n (representing the total number of apples to pack), return the minimum number of bags required. If it is not possible to pack all apples with these two types of bags, return -1.
*/
int minBagsBrute(int apple) {
	if (apple < 0)
		return -1;

	int bag8 = apple >> 3; // apple/8
	int rest = apple - (bag8 << 3);
	while (bag8 >= 0) {
		if (rest % 6 == 0)
			return bag8 + (rest / 6);

		else {
			bag8--;
			rest += 8;
		}
	}
	return -1;
}

int minBagsInduction(int apple) {
	if ((apple & 1) != 0)
		return -1;

	if (apple < 18)
		return apple == 0 ?
		0 : (apple == 6 || apple == 8) ?
		1 : (apple == 12 || apple == 14 || apple == 16) ?
		2 : -1;

	return (apple - 18) / 8 + 3;
}

void testMinBags() {
	cout << "Testing results for apples from 0 to 100:\n";
	for (int apple = 0; apple <= 100; ++apple) { // Loop through 0 to 100
		int bruteResult = minBagsBrute(apple);
		int inductionResult = minBagsInduction(apple);
		cout << "For apple = " << apple << ": Brute force: "
			<< bruteResult << ", Induction: "
			<< inductionResult << endl;
	}
}

/*
Who Will Win the Grass Game?
There is a pile of N portions of grass in a warehouse, and two players, a cow and a sheep, are taking turns eating the grass. The cow always goes first. Each player must eat a number of portions that is a power of 4: 1, 4, 16, 64, ....
Both players are extremely intelligent and play optimally to maximize their chances of winning. The player who cannot make a valid move (because there is no grass left to eat) loses the game.
Given the integer N, determine which player will win if both play optimally.
*/
string whoWinBrute(int n) {
	if (n < 5)
		return (n == 0 || n == 2) ? "Loser" : "Winner";

	int want = 1;
	while (want <= n) {
		if (whoWinBrute(n - want) == "Loser")
			return "Winner";

		if (want <= (n / 4))
			want *= 4;
		else
			break;
	}
	return "Loser";
}

string whoWinInduction(int n) {
	if (n % 5 == 0 || n % 5 == 2)
		return "Loser";
	else
		return "Winner";
}

int mainWhoWin() {
	for (int i = 1; i <= 50; i++)
		cout << "i:" << i << ", whoWinBrute: " << whoWinBrute(i)
		<< ", whoWinInduction: " << whoWinInduction(i)
		<< endl;
	return 0;
}

/*
Determine If a Number Can Be Expressed as a Sum of Consecutive Integers

Define a number as valid if it can be expressed as the sum of two or more consecutive positive integers. Examples:
5 = 2 + 3, so 5 is valid.
12 = 3 + 4 + 5, so 12 is valid.
1 is not valid, because it requires at least two integers to form a sum.
2 = 1 + 1 is not valid, because the numbers on the right side are not consecutive positive integers.
Given an integer N, return whether N can be expressed as the sum of two or more consecutive positive integers.
*/
bool isConsecutiveSumBrute(int num) {
	for (int start = 1; start <= num; start++) {
		int sum = start;
		for (int j = start + 1; j <= num; j++) {
			if (sum + j > num)
				break;
			if (sum + j == num)
				return true;

			sum += j;
		}
	}
	return false;
}

/*
Based on the results of brute-force attempts, it can be concluded that when the number num is a power of 2, the result is false; otherwise, the result is true.
*/
bool isConsecutiveSumInduction(int num) {
	return num != (num & (-num));
}

int mainIsConsecutiveSum() {
	for (int i = 1; i <= 50; i++)
		cout << "i:" << i << ", isConsecutiveSumBrute: " << isConsecutiveSumBrute(i)
		<< ", isConsecutiveSumInduction: " << isConsecutiveSumInduction(i)
		<< endl;
	return 0;
}