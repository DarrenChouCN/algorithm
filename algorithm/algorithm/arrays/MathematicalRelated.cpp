#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
Missing Two Numbers
You are given an array with all the numbers from 1 to N appearing exactly once, except for two number that is missing. How can you find the missing number in O(N) time and 0(1) space?

1. Sum Formula : S=(N*(N+1))/2
2. Square Sum Formula: S=(N*(N+1)*(2N+1))/6
3. Let the missing numbers be x and y.
	So x+y=S-sum_actual and
	x^2+y^2=S(square)-sum_square_actual

Time Complexity: O(N)
Space Complexity: O(1)
*/
pair<int, int> findMissingNumbers(vector<int>& nums, int N) {
	long long S = (N * (N + 1)) / 2;
	long long S_square = (N * (N + 1) * (2 * N + 1)) / 6;

	long long sum_actual = 0, sum_square_actual = 0;

	for (int num : nums)
	{
		sum_actual += num;
		sum_square_actual += (long long)num * num;
	}

	long long sum_diff = S - sum_actual;//x+y
	long long square_sum_diff = S_square - sum_square_actual;//x^2+y^2

	//x^2+y^2=(x+y)^2-2xy -> xy=((x+y)^2-x^2+y^2)/2
	long long sum_xy = (sum_diff * sum_diff - square_sum_diff) / 2;

	long long x_plus_y = sum_diff;
	long long x_times_y = sum_xy;

	// sqrt((x+y)^2-4xy)=sqrt((x-y)^2)=x-y
	int discriminant = sqrt(x_plus_y * x_plus_y - 4 * x_times_y);

	int x = (x_plus_y + discriminant) / 2;
	int y = x_plus_y - x;

	return { x,y };
}

int mainFindMissingNumbers() {
	vector<int> nums = { 1, 2, 4, 6 }; 
	int N = 6;

	pair<int, int> result = findMissingNumbers(nums, N);
	cout << "Missing numbers are: " << result.first << " and " << result.second << endl;

	return 0;
}


/*
Minimize Manhattan Distances
You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
The distance between two points is defined as their Manhattan distance.
Return the minimum possible value for maximum distance between any two points by removing exactly one point.

A Mathematical Proof
Given the Manhattan distance formula:
	D((x1,y1),(x2,y2))=|x1-x2|+|y1-y2|

This can be rewritten as:
	D=max(|(x1+y1)-(x2+y2)|,|(x1-y1)-(x2-y2)|)

Thus, the problem reduces to calculating the maximum difference between the following expressions for any two points (x,y):
	A=x+y, B=x-y, C=-x+y, D=-x-y

Therefore, it is sufficient to find the maximum and minimum values of A, B, C and D across all points in the set. The maximum Manhattan distance will be determined by the maximum difference between these values.
By iterating through each point, compute the values of A, B, C and D, and track the maximum and minimum for each expression. After completing the iteration, the minimum difference between the maximum and minimum values across all four expressions will yield the minimum possible maximum Manhattan distance after removing one point.

Time Complexity: O(N)
Space Complexity: O(1)
*/
int findMaxManhattanDistance(vector<pair<int, int>>& points) {
	int maxA = INT_MIN, minA = INT_MAX;
	int maxB = INT_MIN, minB = INT_MAX;
	int maxC = INT_MIN, minC = INT_MAX;
	int maxD = INT_MIN, minD = INT_MAX;

	for (const auto& point : points)
	{
		int x = point.first;
		int y = point.second;

		maxA = max(maxA, x + y);
		minA = min(minA, x + y);

		maxB = max(maxB, x - y);
		minB = min(minB, x - y);

		maxC = max(maxC, -x + y);
		minC = min(minC, -x + y);

		maxD = max(maxD, -x - y);
		minD = min(minD, -x - y);
	}

	int maxDistA = maxA - minA;
	int maxDistB = maxB - minB;
	int maxDistC = maxC - minC;
	int maxDistD = maxD - minD;

	return min({ maxDistA, maxDistB, maxDistC, maxDistD });
}

int mainFindMaxManhattanDistance() {
	vector<pair<int, int>> points = { {3, 10}, {5, 15}, {10, 2}, {4, 4} };

	cout << "Minimum possible maximum Manhattan distance after removing one point: "
		<< findMaxManhattanDistance(points) << endl;

	return 0;
}