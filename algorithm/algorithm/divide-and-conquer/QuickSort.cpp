#include <iostream>
#include <vector>
#include <cstdlib> // For rand()

using namespace std;

/*
Partitioning an Array
The goal is to partition an array based on a given pivot value, such that all elements smaller than the pivot are placed on the left side of the array, and all elements greater than the pivot are placed on the right side.

Use a two-pointer or one-pointer approach to rearrange the elements, placing smaller elements to the left and larger elements to the right. This process involves traversing the array once and swapping elements to achieve the partition.

Time Complexity:O(N) Space Complexity:O(1)
*/
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

/*
Dutch National Flag
The Dutch National Flag problem involves partitioning an array into three parts based on a given pivot value:
1. Elements less than the pivot go to the left.
2. Elements equal to the pivot stay in the middle.
3. Elements greater than the pivot go to the right.

The solution uses a three-pointer approach.
1. The left pointer tracks the boundary of elements smaller than the pivot.
2. The right pointer tracks the boundary of elements larger than the pivot.
3. The current pointer traverses the array.

Time Complexity:O(N) Space Complexity:O(1)
*/
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

/*
Quick Sorting Optimization
1. Three-way partitioning (Dutch National Flag problem): This optimization reduces redundant comparisons and recursion for elements that are equal to the pivot. For arrays with many equal elements, this optimization significantly improves efficiency.
2. Random pivot selection: This strategy avoids the potential imbalance that could occur when using a fixed pivot, which might lead to worst-case performance O(N^2). By selecting the pivot randomly, more balanced partitions are likely to occur overall, maintaining a stable time complexity of O(nlogn).

Explanation:
1. The recursive QuickSort algorithm now integrates both random pivot selection and three-way partitioning, which improves the performance when handling arrays with duplicate elements and ensures more balanced partitions.
2. The average time complexity remains O(nlogn), but this combined version performs better when handling arrays with many duplicates due to fewer redundant comparisons.

Time Complexity:O(NlogN) Space Complexity:O(N)
*/
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

void printQuickSortArray(const vector<int>& arr) {
	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}

int mainQuickSort() {
	vector<int> arr = { 3, 9, 2, 4, 7, 6, 3, 5, 8 };

	cout << "Original array: ";
	printQuickSortArray(arr);

	quickSort(arr, 0, arr.size() - 1);

	cout << "Sorted array: ";
	printQuickSortArray(arr);

	return 0;
}
