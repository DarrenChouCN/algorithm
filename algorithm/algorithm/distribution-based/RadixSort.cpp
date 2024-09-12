#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Radix Sort
The sorting process is repeated for each digit, starting from the least significant digit and moving toward the most significant digit. By sorting based on each digit and using a stable sorting method (such as counting sort for each digit), Radix Sort guarantees that by the time all digits have been processed, the entire array is sorted correctly.

Important Information
1. In Radix Sort, a prefix sum array is used to divide the array elements into segments based on the current digit being processed, such as the least significant digit, followed by the next higher digit, and so on. Each digit value has a corresponding range in the output array. The prefix sum indicates the range of indices where elements with the same digit value should be placed. This ensures that each element is assigned a unique position, preventing any conflict or overwriting during placement in the output array.

2. To maintain stability, meaning that elements with the same digit retain their relative order from the original array, the input array is traversed from the back to the front during the placement of elements into the output array. This approach ensures that when multiple elements share the same digit value, those that appear later in the input array are placed after those that appeared earlier, thereby preserving the original order of equal elements.

Time and Space Complexity: O(n+k), O(d*(n+k))
*/
int getDigit(int num, int exp) {
	return (num / exp) % 10;
}

void countingSort(vector<int>& arr, int exp) {
	int n = arr.size();
	vector<int> output(n);
	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
		count[getDigit(arr[i], exp)]++;

	// prefix sum
	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--)
	{
		int digit = getDigit(arr[i], exp);
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
	int maxValue = *max_element(arr.begin(), arr.end());

	for (int exp = 1; maxValue / exp > 0; exp *= 10)
		countingSort(arr, exp);
}

int mainRadixSort() {
	vector<int> arr = { 170, 45, 75, 90, 802, 24, 2, 66 };

	cout << "Original array: ";
	for (int num : arr) cout << num << " ";
	cout << endl;

	radixSort(arr);

	cout << "Sorted array: ";
	for (int num : arr) cout << num << " ";
	cout << endl;

	return 0;
}