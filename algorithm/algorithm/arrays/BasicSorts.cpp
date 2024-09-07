#include <iostream>
#include <vector>

using namespace std;

/*
Selection Sort

For ascending order, iterate through the array, select the smallest element from the unsorted portion, and place it at the end of the sorted portion. For descending order, select the largest element and perform the same operation.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
void selectionSort(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}


/*
Bubble Sort

For ascending order, iterate through the array and compare adjacent elements. If the previous element is greater than the next, swap their positions. Repeat this process until the array is sorted. For descending order, the comparison is reversed.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
void bubbleSort(vector<int>& arr, bool ascending = true) {
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (ascending ? (arr[j] > arr[j + 1]) : (arr[j] < arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}


/*
Insertion Sort
Iterate through the array, select an element from the unsorted portion, and insert it into the appropriate position within the sorted portion, maintaining the order.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
void insertionSort(vector<int>& arr) {
	int n = arr.size();
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}