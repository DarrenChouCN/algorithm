## Master Theorem
The Master Theorem is a crucial for analyzing the time complexity of recursive algorithms, especially divide-and-conquer algorithms. It applies to recurrences of the following form:
		
		T(n) = aT(n/b) + O(n^d)

Where:
1. T(n) represents the time complexity for a problem of size n.
2. a is the number of subproblems at each recursive step.
3. b is the factor by which the problem size is reduced in each recursion (often division by b).
4. O(n^d) is the cost of dividing the problem and combining the results.

The Master Theorem determines the time complexity based on the relationship between a, b, and d. There are three main cases:

- Case 1: If a>b^d, i.e., log_b(a)>d, then the time complexity is:

		T(n) = O(n^(log_b(a)))

- Case 2: If a=b^d, i.e., logb(a)=d, then the time complexity is:

		T(n) = O(n^d*(log_b(a)))

- Case 3: If a<b^d, i.e., logb(a)<d, then the time complexity is:

    	T(n) = O(n^d)


## Merge Sort
Merge Sort is a fundamental recursive algorithm with the following core ideas:

1. The overall process is a simple recursion: sort the left side, sort the right side, and then merge them to make the whole array ordered, using an external sorting method.
2. The time complexity is lower than O(n^2) because, compared to selection or insertion sort, merge sort reduces the number of comparisons. This is achieved by comparing already sorted subarrays, rather than individual elements, as the recursion progresses to larger portions of the array.
3. According to the application of the Master Theorem in merge sort, a=2, b=2, and d=1. Thus, the time complexity is O(n^d*(logN)), which simplifies to O(NlogN). Since additional space is required to store temporary variables during merging, the space complexity is O(n).

Time and Space Complexity: O(NlogN), O(n)

```cpp
void merge(vector<int>& arr, int left, int mid, int right) {
	
	int n1 = mid - left + 1, n2 = right - mid;
	vector<int> L(n1), R(n2);
		
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = arr[mid + 1 + i];
		
	// Merge the temporary arrays back into arr
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
		
	// Copy the remaining elements of L[] and R[]
	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		
		merge(arr, left, mid, right);
	}
}
```

## Small Sum
In an array, for each element, find the sum of all the numbers to its left that are smaller than the current number.

By utilizing the merge sort technique, the comparisons between individual elements can be transformed into range-based comparisons, reducing the overall number of comparisons and improving time complexity.

1. Use merge sort to recursively divide the array into two halves.
2. During the merge step, calculate the small sum by identifying the elements in the left subarray that are smaller than those in the right subarray.
3. Accumulate the small sum during the merge process.
4. Return the total small sum after the complete merging process.

Time and Space Complexity: O(NlogN), O(n)
	
```cpp
int mergeAndCountSmallSum(vector<int>& arr, int left, int mid, int right) {
	int n1 = mid - left + 1, n2 = right - mid;
	vector<int> L(n1), R(n2);
		
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = arr[mid + 1 + i];
		
	// Merge the temporary arrays back into arr
	int i = 0, j = 0, k = left;
	int smallSum = 0;
		
	while (i < n1 && j < n2) {
		if (L[i] < R[j]) {
			smallSum += L[i] * (n2 - j);
			arr[k++] = L[i++];
		}
		else
		{
			arr[k++] = R[j++];
		}
	}
		
	// Copy the remaining elements of L[] and R[]
	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];
		
	return smallSum;
}
		
int mergeSortAndCountSmallSum(vector<int>& arr, int left, int right) {
	if (left >= right) return 0;
		
	int mid = left + (right - left) / 2;
	int leftSum = mergeSortAndCountSmallSum(arr, left, mid);
	int rightSum = mergeSortAndCountSmallSum(arr, mid + 1, right);
	int mergeSum = mergeAndCountSmallSum(arr, left, mid, right);
		
	return leftSum + rightSum + mergeSum;
}
```


## Reverse Pairs
The reverse pairs Problem is an extension of the merge sort algorithm. The task is to count and output all the reverse pairs in an array. A reverse pair is defined as a pair of elements where the left element is greater than the right element.

The reverse pairs problem is an extension of the merge sort algorithm. During the sorting process, when an element in the left half is found to be greater than an element in the right half, the number of reverse pairs is calculated by subtracting the indices. Specifically, the number of reverse pairs is the difference in indices between the current element in the left half and the right half. Each such reverse pair is then printed as it is discovered.

Time and Space Complexity: O(NlogN), O(n)

```cpp
int mergeAndCountReversePairs(vector<int>& arr, int left, int mid, int right) {
	int n1 = mid - left + 1, n2 = right - mid;
	vector<int> L(n1), R(n2);
		
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = arr[mid + 1 + i];
		
	int i = 0, j = 0, k = left;
	int reverseCount = 0;
		
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		}
		else
		{
			for (int p = i; p < n1; p++)
				cout << "(" << L[p] << ", " << R[j] << ")" << endl;
			reverseCount += (n1 - i);
			arr[k++] = R[j++];
		}
	}
		
	// Copy the remaining elements of L[] and R[]
	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];
		
	return reverseCount;
}
		
int mergeSortAndCountReversePairs(vector<int>& arr, int left, int right) {
	if (left >= right) return 0;
		
	int mid = left + (right - left) / 2;
	int leftPairs = mergeSortAndCountReversePairs(arr, left, mid);
	int rightPairs = mergeSortAndCountReversePairs(arr, mid + 1, right);
	int mergeParis = mergeAndCountReversePairs(arr, left, mid, right);
		
	return leftPairs + rightPairs + mergeParis;
}
```

## Partitioning an Array
The goal is to partition an array based on a given pivot value, such that all elements smaller than the pivot are placed on the left side of the array, and all elements greater than the pivot are placed on the right side.

Use a two-pointer or one-pointer approach to rearrange the elements, placing smaller elements to the left and larger elements to the right. This process involves traversing the array once and swapping elements to achieve the partition.

Time and Space Complexity: O(N), O(1)

```cpp
void partitionArray(vector<int>& arr, int pivot) {
	int left = 0, right = arr.size() - 1;
	while (left <= right) {
		if (arr[left] < pivot)
			left++;
		
		else if (arr[right] >= pivot)
			right--;
		
		else
			swap(arr[left++], arr[right--]);
	}
}
```

## Dutch National Flag
The Dutch National Flag problem involves partitioning an array into three parts based on a given pivot value:

1. Elements less than the pivot go to the left.
2. Elements equal to the pivot stay in the middle.
3. Elements greater than the pivot go to the right.

The solution uses a three-pointer approach.

1. The left pointer tracks the boundary of elements smaller than the pivot.
2. The right pointer tracks the boundary of elements larger than the pivot.
3. The current pointer traverses the array.

Time and Space Complexity: O(1)

```cpp
void dutchNationalFlag(vector<int>& arr, int pivot) {
	int left = 0;                // Boundary for elements less than pivot
	int right = arr.size() - 1;   // Boundary for elements greater than pivot
	int current = 0;              // Current pointer to traverse the array
		
	while (current <= right) {
		if (arr[current] < pivot)
			// Swap with the left boundary and move both current and left pointers
			swap(arr[left++], arr[current++]);
		
		else if (arr[current] > pivot)
			// Swap with the right boundary and move the right pointer
			swap(arr[current], arr[right--]);
		
		else
			// If equal to pivot, just move the current pointer
			current++;
	}
}
```

## Quick Sorting Optimization
1. Three-way partitioning (Dutch National Flag problem): This optimization reduces redundant comparisons and recursion for elements that are equal to the pivot. For arrays with many equal elements, this optimization significantly improves efficiency.
2. Random pivot selection: This strategy avoids the potential imbalance that could occur when using a fixed pivot, which might lead to worst-case performance O(N^2). By selecting the pivot randomly, more balanced partitions are likely to occur overall, maintaining a stable time complexity of O(nlogn).

Explanation:

1. The recursive QuickSort algorithm now integrates both random pivot selection and three-way partitioning, which improves the performance when handling arrays with duplicate elements and ensures more balanced partitions.
2. The average time complexity remains O(nlogn), but this combined version performs better when handling arrays with many duplicates due to fewer redundant comparisons.

Time and Space Complexity: O(NlogN), O(N)

```cpp
pair<int, int> partition(vector<int>& arr, int low, int high) {
	// Randomly select a pivot index
	int randomPivotIndex = low + rand() % (high - low + 1);
	int pivot = arr[randomPivotIndex];
		
	// Move pivot to the end of the array for partitioning
	swap(arr[randomPivotIndex], arr[high]);
		
	int left = low; // Boundary for elements less than pivot
	int right = high; // Boundary for elements greater than pivot
	int current = low;
		
	while (current <= right) {
		if (arr[current] < pivot)
			swap(arr[left++], arr[current++]);
		
		else if (arr[current] > pivot)
			swap(arr[current], arr[right--]);
		
		else // arr[current] == pivot
			current++; 
	}
	// return the range where elements are equal to pivot
	return { left,right };
}
		
void quickSort(vector<int>& arr, int low, int high) {
	if (low < high) {
		// Perform partition and get the boundaries of the pivot element
		pair<int, int> pivotRange = partition(arr, low, high);
		
		// Recursively sort the parts that are less than and greater than the pivot
		quickSort(arr, low, pivotRange.first - 1);
		quickSort(arr, pivotRange.second + 1, high);
	}
}
```

## BFPRT algorithm
The BFPRT algorithm is used to find the k-th smallest element in an unsorted array. It borrows the idea of partitioning from the quicksort algorithm, selecting a pivot value and dividing the array into three regions: elements less than, equal to, and greater than the pivot. Unlike quicksort, which recursively sorts each part, BFPRT only processes the part that contains the target element, saving time by avoiding unnecessary sorting.

Additionally, the BFPRT algorithm optimizes the pivot selection process by ensuring the pivot is chosen in a way that minimizes the likelihood of worst-case time complexity. It does this by dividing the array into small groups, sorting each group, and selecting the median of each group. The median of these medians is then used as the pivot, making the partitioning more balanced and efficient.

Algorithm Steps:
1. Select the pivot value (pivotValue): Divide the array into groups of 5 elements, sort each group (using any method), and choose the median of each group. The median of these medians becomes the pivot value.
2. Partition the array: Using the chosen pivot, partition the array into three regions: elements less than, equal to, and greater than the pivot.
3. Determine the next step: If the k-th element lies in the region equal to the pivot, return it directly. Otherwise, recursively apply the process to the region where the k-th element lies, selecting a new pivot and repeating the steps.

Time and Space Complexity: O(n) and O(logn)

```cpp
int medianOfMedians(vector<int>& arr, int L, int R);
int bfprt(vector<int>& arr, int L, int R, int k);

// Insertion sort for the subarray arr[L...R]
void insertionSort(vector<int>& arr, int L, int R) {
	for (int i = L + 1; i <= R; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= L && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

int getMedian(vector<int>& arr, int L, int R) {
	insertionSort(arr, L, R);
	return arr[(L + R) / 2];
}

// Recursively find the median of medians in arr[L...R]
int medianOfMedians(vector<int>& arr, int L, int R) {
	int size = R - L + 1;

	int offset = (size % 5 == 0) ? 0 : 1;
	vector<int> medianArray(size / 5 + offset);

	for (int team = 0; team < medianArray.size(); ++team) {
		int teamFirst = L + team * 5;
		medianArray[team] = getMedian(arr, teamFirst, min(R, teamFirst + 4));
	}

	return bfprt(medianArray, 0, medianArray.size() - 1, medianArray.size() / 2);
}

vector<int> partition(vector<int>& arr, int L, int R, int pivotValue) {
	int less = L - 1;
	int more = R + 1;
	int cur = L;

	while (cur < more) {
		if (arr[cur] < pivotValue)
			swap(arr[++less], arr[cur++]);

		else if (arr[cur] > pivotValue)
			swap(arr[cur], arr[--more]);

		else
			++cur;
	}

	return { less + 1,more - 1 };
}

int bfprt(vector<int>& medianArray, int L, int R, int k) {
	if (L == R) return medianArray[L];

	int pivot = medianOfMedians(medianArray, L, R);
	vector<int> range = partition(medianArray, L, R, pivot);

	if (k >= range[0] && k <= range[1])
		return medianArray[k];

	else if (k < range[0])
		return bfprt(medianArray, L, range[0] - 1, k);

	else
		return bfprt(medianArray, range[1] + 1, R, k);
}

int minKth(vector<int>& arr, int k) {
	return bfprt(arr, 0, arr.size() - 1, k);
}
```


## Segment Tree
A segment tree is a tree-like data structure used for storing statistical information about intervals or segments. It is designed to allow efficient range queries and updates, making it especially suitable for dynamic datasets.

The segment tree¡¯s query and update operations are implemented by recursively dividing intervals into sub-intervals, a classic divide-and-conquer approach. This enables the segment tree to handle large datasets efficiently, achieving a time complexity of O(logn) for queries and updates.

```cpp
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
```



## Falling Squares
There are several squares being dropped onto the X-axis of a 2D plane.
You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
After each square is dropped, you must record the height of the current tallest stack of squares.
Return an integer array ans where ans[i] represents the height described above after dropping the ith square.

LeetCode: https://leetcode.cn/problems/falling-squares/

Time and Space Complexity: O(NlogN) and O(N)

```cpp
class FallingSquares {

public:
	vector<int> fallingSquares(vector<vector<int>>& positions) {
		/*
		In the Falling Squares problem, the main focus is on the maximum height of stacked squares after each block falls. Therefore, the classic segment tree can be simplified and adjusted to retain only the logic for computing maximum values, using only a lazy array for lazy propagation. There is no need to maintain a range sum (sum) as in a traditional segment tree.
		*/
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
				return max(
					queryRange(L, R, left, mid, root * 2),
					queryRange(L, R, mid + 1, right, root * 2 + 1)
				);
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

		/*
		Coordinate Compression
		Coordinate compression is used to map original coordinates to a smaller index range, allowing efficient segment tree construction within a limited index space. Through this mapping, original coordinates are quickly converted to compressed indices in O(1) time. The segment tree maintains the maximum height for each interval based on these compressed indices. For each falling square, the interval's current maximum height is queried, a new height is calculated, and the segment tree is updated accordingly. This approach reduces the space complexity of segment tree operations and enables range queries and updates in O(logN) time.
		*/ 
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

		vector<int> result;
		int maxHeight = 0;
		SegmentTree segmentTree(idx);

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
```