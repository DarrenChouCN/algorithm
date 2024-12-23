#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

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

// Max Top 1 : Sorting
// Time and Space Complexity: O(NlogN) and O(K)
vector<int> maxTop1(vector<int>& arr, int k) {
	if (arr.empty())
		return vector<int>();


	int N = arr.size();
	k = min(N, k);

	sort(arr.begin(), arr.end());

	vector<int> ans(k);
	for (int i = N - 1, j = 0; j < k; i--, j++) {
		ans[j] = arr[i];
	}

	return ans;
}


// Max Top 2 : heap
// Time and Space Complexity: O(N + KlogN) and O(K) 
void swap(vector<int>& arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void heapInsert2(vector<int>& arr, int index) {
	while (index > 0 && arr[index] > arr[(index - 1) / 2]) {
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}

void heapify(vector<int>& arr, int index, int heapSize) {
	int left = 2 * index + 1;
	while (left < heapSize) {
		int largest = (left + 1 < heapSize && arr[left + 1] > arr[left]) ?
			left + 1 : left;
		largest = arr[largest] > arr[index] ? largest : index;

		if (largest == index)
			break;

		swap(arr, largest, index);
		index = largest;
		left = 2 * index + 1;
	}
}

vector<int> maxTopK2(vector<int>& arr, int k) {
	if (arr.empty()) {
		return vector<int>();
	}

	int N = arr.size();
	k = min(N, k);

	// Build the max heap
	for (int i = N - 1; i >= 0; i--) {
		heapify(arr, i, N);
	}

	// Extract the top k elements
	int heapSize = N;
	swap(arr, 0, --heapSize);
	int count = 1;

	while (heapSize > 0 && count < k) {
		heapify(arr, 0, heapSize);
		swap(arr, 0, --heapSize);
		count++;
	}

	vector<int> ans(k);
	for (int i = N - 1, j = 0; j < k; i--, j++) {
		ans[j] = arr[i];
	}

	return ans;
}

// Max Top 3 : partition
// Time and Space Complexity: O(n + k * logk) and O(K) 
int minKth3(vector<int>& arr, int index) {
	int L = 0;
	int R = arr.size() - 1;
	while (L < R) {
		int pivot = arr[L + rand() % (R - L + 1)];
		vector<int> range = partition(arr, L, R, pivot);
		if (index < range[0]) {
			R = range[0] - 1;
		}
		else if (index > range[1]) {
			L = range[1] + 1;
		}
		else {
			return pivot;
		}
	}
	return arr[L];
}


vector<int> maxTopK3(vector<int>& arr, int k) {
	if (arr.empty())
		return vector<int>();

	int N = arr.size();
	k = min(N, k);

	int num = minKth(arr, N - k);
	vector<int> ans(k);
	int index = 0;

	for (int i = 0; i < N; i++)
		if (arr[i] > num)
			ans[index++] = arr[i];

	while (index < k)
		ans[index++] = num;

	sort(ans.begin(), ans.end());

	for (int L = 0, R = k - 1; L < R; L++, R--) {
		swap(ans[L], ans[R]);
	}

	return ans;
}
