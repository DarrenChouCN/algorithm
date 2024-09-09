/*
Master Theorem
The Master Theorem is a crucial for analyzing the time complexity of recursive algorithms, especially divide-and-conquer algorithms. It applies to recurrences of tghe following form:
	T(n) = aT(n/b) + O(n^d)

Where:
	1. T(n) represents the time complexity for a problem of size n.
	2. a is the number of subproblems at each recursive step.
	3. b is the factor by which the problem size is reduced in each recursion (often division by b).
	4. O(n^d) is the cost of dividing the problem and combining the results.

The Master Theorem determines the time complexity based on the relationship between a, b, and d. There are three main cases:
	1. Case 1: If a>b^d, i.e., logb(a)>d, then the time complexity is:
		T(n) = O(n^(logb(a)))
	2. Case 2: If a=b^d, i.e., logb(a)=d, then the time complexity is:
		T(n) = O(n^d*(logb(a)))
	3. Case 3: If a<b^d, i.e., logb(a)<d, then the time complexity is:
	T(n) = O(n^d)
*/
#include <iostream>
#include <vector>

using namespace std;

/*
Merge Sort
Merge Sort is a fundamental recursive algorithm with the following core ideas:
a. The overall process is a simple recursion: sort the left side, sort the right side, and then merge them to make the whole array ordered, using an external sorting method.
b. The time complexity is lower than O(n^2) because, compared to selection or insertion sort, merge sort reduces the number of comparisons. This is achieved by comparing already sorted subarrays, rather than individual elements, as the recursion progresses to larger portions of the array.
c. According to the application of the Master Theorem in merge sort, a=2, b=2, and d=1. Thus, the time complexity is O(n^d*(logN)), which simplifies to O(NlogN). Since additional space is required to store temporary variables during merging, the space complexity is O(n).

Time Complexity:O(NlogN) Space Complexity:O(n)
*/
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


/*
Small Sum
In an array, for each element, find the sum of all the numbers to its left that are smaller than the current number.

By utilizing the merge sort technique, the comparisons between individual elements can be transformed into range-based comparisons, reducing the overall number of comparisons and improving time complexity.
1. Use merge sort to recursively divide the array into two halves.
2. During the merge step, calculate the small sum by identifying the elements in the left subarray that are smaller than those in the right subarray.
3. Accumulate the small sum during the merge process.
4. Return the total small sum after the complete merging process.

Time Complexity:O(NlogN) Space Complexity:O(n)
*/
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

/*
Reverse Pairs
The reverse pairs Problem is an extension of the merge sort algorithm. The task is to count and output all the reverse pairs in an array. A reverse pair is defined as a pair of elements where the left element is greater than the right element.

The reverse pairs problem is an extension of the merge sort algorithm. During the sorting process, when an element in the left half is found to be greater than an element in the right half, the number of reverse pairs is calculated by subtracting the indices. Specifically, the number of reverse pairs is the difference in indices between the current element in the left half and the right half. Each such reverse pair is then printed as it is discovered.

Time Complexity:O(NlogN) Space Complexity:O(n)
*/
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