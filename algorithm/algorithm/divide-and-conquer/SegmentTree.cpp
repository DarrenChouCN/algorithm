#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*
Segment Tree
A segment tree is a tree-like data structure used for storing statistical information about intervals or segments. It is designed to allow efficient range queries and updates, making it especially suitable for dynamic datasets.
The segment tree¡¯s query and update operations are implemented by recursively dividing intervals into sub-intervals, a classic divide-and-conquer approach. This enables the segment tree to handle large datasets efficiently, achieving a time complexity of O(logn) for queries and updates.
*/
class SegmentTree {
private:
	/*
	Initial Value
	1. arr: Stores the initial data used as the basis for building the segment tree.
	2. sum: Stores the sum of each node's managed range, with a length of 4 times the original array.
	3. lazy: Manages incremental updates. Stores an increment value to be applied later when the relevant range is accessed.
	4. change: Manages overwrite updates. When a range needs to be set to a fixed value, this target value is stored in change.
	5. update: Indicates whether a node has a pending overwrite update. true means the node and its range need to be updated to the value in change.
	*/
	int MAXN;
	vector<int> arr; // original array
	vector<int> sum; // for range sums
	vector<int> lazy; // for delayed addition updates
	vector<int> change; // for delayed overwrite updates
	vector<bool> update; // for overwrite operations

	// Updates the root node's value.
	// Combines the values of its left and right children to update the sum of the root node's range.
	void pushUp(int root) {
		sum[root] = sum[root * 2] + sum[root * 2 + 1];
	}

	/*
	pushDown(root, leftSize, rightSize): Propagates delayed updates to child nodes

	If update[root] == true, indicating a pending overwrite, propagate it to the left and right children.
		1. Sets the sums of the left and right children to change[root] * leftSize and change[root] * rightSize, effectively overwriting them with the target value.
		2. Marks update[left child] and update[right child] as true and passes change[root] to their change arrays.
		3. Resets update[root] to false to indicate the overwrite has been propagated.

	If lazy[root] != 0, indicating a pending addition, propagate it to the left and right children.
		1. Increases the sums of the left and right children by lazy[root] * leftSize and lazy[root] * rightSize, applying the increment.
		2. Adds lazy[root] to lazy[left child] and lazy[right child] to propagate the increment value.
		3. Resets lazy[root] to 0, marking the addition as propagated.
	*/
	void pushDown(int root, int leftSize, int rightSize) {
		if (update[root]) {
			update[root * 2] = true;
			update[root * 2 + 1] = true;

			change[root * 2] = change[root];
			change[root * 2 + 1] = change[root];

			lazy[root * 2] = 0;
			lazy[root * 2 + 1] = 0;

			sum[root * 2] = change[root] * leftSize;
			sum[root * 2 + 1] = change[root] * rightSize;

			update[root] = false;
		}
		if (lazy[root] != 0) {
			lazy[root * 2] += lazy[root];
			lazy[root * 2 + 1] += lazy[root];

			sum[root * 2] += lazy[root] * leftSize;
			sum[root * 2 + 1] += lazy[root] * rightSize;

			lazy[root] = 0;
		}
	}


public:
	SegmentTree(const vector<int>& origin) {
		MAXN = origin.size() + 1;
		arr.resize(MAXN);
		for (int i = 1; i < MAXN; i++)
			arr[i] = origin[i - 1];

		sum.resize(MAXN * 4);
		lazy.resize(MAXN * 4, 0);
		change.resize(MAXN * 4);
		update.resize(MAXN * 4, false);
	}

	void build(int left, int right, int root) {
		if (left == right) {
			sum[root] = arr[left];
			return;
		}

		int mid = (left + right) / 2;
		build(left, mid, root * 2);
		build(mid + 1, right, root * 2 + 1);
		pushUp(root);
	}


	/*
	The functions addRange, updateRange, and queryRange in a segment tree all utilize recursive binary division to handle their respective operations efficiently by continuously dividing and processing relevant sections of the interval. This approach embodies the core concept of the segment tree, allowing it to handle interval updates and queries in O(log N) time complexity.
	*/
	void updateRange(int leftBound, int rightBound, int value, int left, int right, int root) {
		if (leftBound <= left && right <= rightBound) {
			update[root] = true;
			change[root] = value;
			sum[root] = value * (right - left + 1);
			lazy[root] = 0;
			return;
		}

		int mid = (left + right) / 2;
		pushDown(root, mid - left + 1, right - mid);
		if (leftBound <= mid) {
			updateRange(leftBound, rightBound, value, left, mid, root * 2);
		}
		if (rightBound > mid) {
			updateRange(leftBound, rightBound, value, mid + 1, right, root * 2 + 1);
		}
		pushUp(root);
	}

	void addRange(int leftBound, int rightBound, int value, int left, int right, int root) {
		if (leftBound <= left && right <= rightBound) {
			sum[root] += value * (right - left + 1);
			lazy[root] += value;
			return;
		}

		int mid = (left + right) / 2;
		pushDown(root, mid - left + 1, right - mid);
		if (leftBound <= mid) {
			addRange(leftBound, rightBound, value, left, mid, root * 2);
		}
		if (rightBound > mid) {
			addRange(leftBound, rightBound, value, mid + 1, right, root * 2 + 1);
		}
		pushUp(root);
	}

	long long queryRange(int leftBound, int rightBound, int left, int right, int root) {
		if (leftBound <= left && right <= rightBound) {
			return sum[root];
		}

		int mid = (left + right) / 2;
		pushDown(root, mid - left + 1, right - mid);
		long long result = 0;
		if (leftBound <= mid) {
			result += queryRange(leftBound, rightBound, left, mid, root * 2);
		}
		if (right > mid) {
			result += queryRange(leftBound, rightBound, mid + 1, right, root * 2 + 1);
		}
		return result;
	}
};

/*
Falling Squares

There are several squares being dropped onto the X-axis of a 2D plane.
You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
After each square is dropped, you must record the height of the current tallest stack of squares.
Return an integer array ans where ans[i] represents the height described above after dropping the ith square.
*/
class FallingSquares {

public:
	vector<int> fallingSquares(vector<vector<int>>& positions) {
		map<int, int> coordinateCompression;
		for (const auto& pos : positions) {
			int left = pos[0];
			int right = pos[0] + pos[1] - 1;
			coordinateCompression[left];
			coordinateCompression[right];
		}

		int idx = 0;
		for (auto& entry : coordinateCompression) {
			entry.second = ++idx;
		}

		class SegmentTree {
		private:
			int n;
			vector<int> tree, lazy;

			void pushDown(int root, int left, int right) {
				if (lazy[root] != 0) {
					tree[root] = max(tree[root], lazy[root]);
					if (left != right) {
						lazy[root * 2] = max(lazy[root * 2], lazy[root]);
						lazy[root * 2 + 1] = max(lazy[root * 2 + 1], lazy[root]);
					}
					lazy[root] = 0;
				}
			}

			void updateRange(int L, int R, int value, int left, int right, int root) {
				pushDown(root, left, right);
				if (R<left || L>right)
					return;
				if (L <= left && right <= R) {
					lazy[root] = value;
					pushDown(root, left, right);
					return;
				}

				int mid = (left + right) / 2;
				updateRange(L, R, value, left, mid, root * 2);
				updateRange(L, R, value, mid + 1, right, root * 2 + 1);
				tree[root] = max(tree[root * 2], tree[root * 2 + 1]);
			}

			int queryRange(int L, int R, int left, int right, int root) {
				pushDown(root, left, right);
				if (R<left || L>right)
					return 0;
				if (L <= left && right <= R)
					return tree[root];
				int mid = (left + right) / 2;
				return max(queryRange(L, R, left, mid, root * 2),
					queryRange(L, R, mid + 1, right, root * 2 + 1));
			}

		public:
			SegmentTree(int size) :n(size) {
				tree.resize(4 * n);
				lazy.resize(4 * n);
			}

			void update(int L, int R, int value) {
				updateRange(L, R, value, 1, n, 1);
			}

			int query(int L, int R) {
				return queryRange(L, R, 1, n, 1);
			}
		};

		SegmentTree segmentTree(idx);
		vector<int> result;
		int maxHeight = 0;

		for (const auto& pos : positions) {
			int left = coordinateCompression[pos[0]];
			int right = coordinateCompression[pos[0] + pos[1] - 1];
			int height = segmentTree.query(left, right) + pos[1];
			segmentTree.update(left, right, height);
			maxHeight = max(maxHeight, height);
			result.push_back(maxHeight);
		}

		return result;
	}
};