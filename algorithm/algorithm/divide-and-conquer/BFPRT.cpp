#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
BFPRT algorithm
The BFPRT algorithm is used to find the k-th smallest element in an unsorted array. It borrows the idea of partitioning from the quicksort algorithm, selecting a pivot value and dividing the array into three regions: elements less than, equal to, and greater than the pivot. Unlike quicksort, which recursively sorts each part, BFPRT only processes the part that contains the target element, saving time by avoiding unnecessary sorting.

Additionally, the BFPRT algorithm optimizes the pivot selection process by ensuring the pivot is chosen in a way that minimizes the likelihood of worst-case time complexity. It does this by dividing the array into small groups, sorting each group, and selecting the median of each group. The median of these medians is then used as the pivot, making the partitioning more balanced and efficient.

Algorithm Steps:
1. Select the pivot value (pivotValue): Divide the array into groups of 5 elements, sort each group (using any method), and choose the median of each group. The median of these medians becomes the pivot value.
2. Partition the array: Using the chosen pivot, partition the array into three regions: elements less than, equal to, and greater than the pivot.
3. Determine the next step: If the k-th element lies in the region equal to the pivot, return it directly. Otherwise, recursively apply the process to the region where the k-th element lies, selecting a new pivot and repeating the steps.

Time and Space Complexity: O(n) and O(logn)
*/
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