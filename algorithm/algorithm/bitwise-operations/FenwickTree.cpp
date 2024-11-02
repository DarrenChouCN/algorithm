#include <vector>

using namespace std;

/*
Fenwick Tree/Binary Indexed Tree (BIT)

Overview: The Fenwick Tree/Binary Indexed Tree (BIT) is a data structure that organizes array elements into groups. This grouping method enables efficient O(logN) time complexity for prefix sum queries and updates. The BIT utilizes binary operations to manage array prefix sums and supports efficient single-element updates.

Mapping Process: Using binary properties, i & -i identifies the range covered by each index i. For prefix sum queries, the sum of the current position and all previous relevant prefix ranges is calculated. For updates, each affected position in the relevant range is adjusted to maintain accurate prefix sums.

Example: For the array [1, 2, 3, 4, 5, 6, 7, 8], prefix sum queries and updates are performed at position i = 6 as follows:
	Binary Representation: In binary, i = 6 is 0110 and -i is 1010, so i & -i = 2. This result indicates that BIT[6] covers a range of length 2, specifically the sum of A[5] and A[6].

	Query: After obtaining the value at BIT[6], the query proceeds by summing values from prior grouped intervals, specifically adding BIT[4] (representing the sum of [A[1], A[4]]).

	Update: To update A[6], each relevant interval following BIT[6] is updated, specifically BIT[6] and BIT[8], as these intervals include the affected element A[6].

Complexity:
Construction Time Complexity: O(nlogn)
Query and Update Time Complexity: O(logn)
Space Complexity: O(n)
*/
class FenwickTree {
public:
	vector<int> BIT;
	int n;

	FenwickTree(const vector<int>& arr) {
		n = arr.size();
		BIT.resize(n + 1, 0);
		for (int i = 0; i < n; ++i) {
			update(i + 1, arr[i]);
		}
	}

	void update(int idx, int delta) {
		while (idx <= n) {
			BIT[idx] += delta;
			idx += idx & -idx;
		}
	}

	int query(int idx) {
		int sum = 0;
		while (idx > 0) {
			sum += BIT[idx];
			idx -= idx & -idx;
		}
		return sum;
	}

	int range_query(int left, int right) {
		return query(right) - query(left - 1);
	}
};

/*
2D Fenwick Tree
A key advantage of the Fenwick Tree (Binary Indexed Tree) over the Segment Tree is its natural extensibility to manage multi-dimensional arrays, such as 2D, 3D, or even higher dimensions.

Construction Time Complexity: O(nlogn*logm)
Query and Update Time Complexity: O(logn*logm)
Space Complexity: O(n*m)
*/
class FenwickTree2D {
public:
	vector<vector<int>> BIT;
	int n, m;

	FenwickTree2D(const vector<vector<int>>& matrix) {
		n = matrix.size();
		m = matrix[0].size();
		BIT.resize(n + 1, vector<int>(m + 1, 0)); // BIT array is initialized to 0

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				update(i + 1, j + 1, matrix[i][j]);
	}

	void update(int row, int col, int delta) {
		for (int i = row; i <= n; i += i & -i)  // Traverse vertically in BIT
			for (int j = col; j <= m; j += j & -j)  // Traverse horizontally in BIT
				BIT[i][j] += delta;
	}

	int query(int row, int col) {
		int sum = 0;
		for (int i = row; i > 0; i -= i & -i) // Traverse vertically in BIT
			for (int j = col; j > 0; j -= j & -j) // Traverse horizontally in BIT
				sum += BIT[i][j];
		return sum;
	}

	int rangeQuery(int row1, int col1, int row2, int col2) {
		return query(row2, col2)
			- query(row1 - 1, col2)
			- query(row2, col1 - 1)
			+ query(row1 - 1, col1 - 1);
	}
};