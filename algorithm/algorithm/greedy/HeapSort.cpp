#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Node Insertion
1. Insert the element at the end of the array and compare it with its parent node (i−1)/2.
2. In a max-heap, if the inserted node’s value is greater than its parent, swap the two elements.
3. Repeat this process (bubble-up) until the element finds its correct position. The same process applies to a min-heap, but the comparison is reversed.

Node Deletion
1. To delete a node in a max-heap, swap the last element with the node to be deleted.
2. Then compare this element with its children. If any child node is larger than the current node, swap the two.
3. Repeat this process (bubble-down) until the element finds its correct position. The same approach applies to a min-heap, but the comparison is reversed.

The time complexity of insertion and deletion operations is primarily determined by the height of the binary tree, which is O(logN).

Time and Space Complexity: O(logN), O(1)
*/
void heapInsert(vector<int>& heap, int value) {
	// Insert the value at the end of the heap
	heap.push_back(value);

	int currentIndex = heap.size() - 1;
	int parentIndex = (currentIndex - 1) / 2; // (i−1)/2

	while (currentIndex > 0 && heap[currentIndex] > heap[parentIndex]) {
		swap(heap[currentIndex], heap[parentIndex]);
		currentIndex = parentIndex;
		parentIndex = (currentIndex - 1) / 2;
	}
}

// remove root element
void heapDelete(vector<int>& heap) {
	if (heap.empty()) return;

	int heapSize = heap.size();

	heap[0] = heap.back();
	heap.pop_back();

	int currentIndex = 0;

	while (currentIndex < heapSize) {
		int leftChildIndex = 2 * currentIndex + 1;
		int rightChildIndex = 2 * currentIndex + 2;
		int largestIndex = currentIndex;

		if (leftChildIndex< heapSize && heap[leftChildIndex]>heap[currentIndex]) {
			largestIndex = leftChildIndex;
		}

		if (rightChildIndex< heapSize && heap[rightChildIndex]>heap[largestIndex]) {
			largestIndex = rightChildIndex;
		}

		if (largestIndex == currentIndex) break;

		swap(heap[currentIndex], heap[largestIndex]);

		currentIndex = largestIndex;
	}
}

/*
Heap Sort
1. Build the heap (either max-heap or min-heap) from the given array.
2. Repeately swap the last element with the root (the largest or smallest element) and adjust the heap to maintain the heap property.
3. Reduce the size of the heap by 1 (size--), meaning the element at the end is in its final sorted position.
4. Continue this process until the array is sorted.

More Information:
1. The time complexity of heap sort is O(nlogn), which comes from building the heap and performing the sort. The space complexity is O(1), as the sorting process is performed in-place using a constant amount of extra space.
2. If the array is already known in advance, the heap can be built directly by adjusting elements from the end of the array to the beginning. This can optimize the heap-building process, but since the adjustment complexity is still O(nlogn), the overall time complexity remains O(nlogn).
3. The priority queue is essentially a heap structure where the element with the highest priority is placed at the top of the heap. Priority comparisons can be managed by implementing a custom comparator to define the priority of elements.

Time and Space Complexity: O(NlogN), O(1)
*/
void heapifyMaxHeap(vector<int>& heap, int heapSize, int rootIndex) {
	int largestIndex = rootIndex;
	int leftChildIndex = 2 * rootIndex + 1;
	int rightChildIndex = 2 * rootIndex + 2;

	if (leftChildIndex< heapSize && heap[leftChildIndex]>heap[largestIndex])
		largestIndex = leftChildIndex;

	if (rightChildIndex< heapSize && heap[rightChildIndex]>heap[largestIndex])
		largestIndex = rightChildIndex;

	if (largestIndex != rootIndex) {
		swap(heap[largestIndex], heap[rootIndex]);

		heapifyMaxHeap(heap, heapSize, largestIndex);
	}
}

void heapSort(vector<int>& arr) {
	int arraySize = arr.size();

	// Build heap
	for (int i = arraySize / 2 - 1; i >= 0; i--)
		heapifyMaxHeap(arr, arraySize, i);

	for (int i = arraySize - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapifyMaxHeap(arr, i, 0);
	}
}


/*
Heap Sort Extension
Given an almost sorted array, where each element's final sorted position will not be more than k positions away from its current position. The task is to sort this array efficiently.

To solve this problem, a min-heap of size k can be used to maintain the order of elements. By continuously adding and removing elements from this heap, the array can be sorted in O(nlogk) time complexity. If k is small, the time complexity can even approach O(n). The goal is to manually implement a min-heap instead of relying on API-based priority queues, as manually maintaining the heap is both educational and practically beneficial in most interview and job situations.

1. Create a min-heap with the first k elements of the array.
2. For the remaining elements, push each new element into the heap and pop the smallest element to place it in its correct position in the sorted array.
3. Once the array has been processed, continue popping the remaining elements from the heap to complete the sorting.
*/
void heapifyMinHeap(vector<int>& heap, int rootIndex) {
	int heapSize = heap.size();
	int smallestIndex = rootIndex;
	int leftChildIndex = rootIndex * 2 + 1;
	int rightChildIndex = rootIndex * 2 + 2;


	if (leftChildIndex < heapSize && heap[leftChildIndex] < heap[smallestIndex])
		smallestIndex = leftChildIndex;

	if (rightChildIndex < heapSize && heap[rightChildIndex] < heap[smallestIndex])
		smallestIndex = rightChildIndex;

	if (smallestIndex != rootIndex) {
		swap(heap[smallestIndex], heap[rootIndex]);

		heapifyMinHeap(heap, smallestIndex);
	}
}

void pushHeap(vector<int>& heap, int element) {
	heap.push_back(element);

	int index = heap.size();
	int parentIndex = (index - 1) / 2;

	while (index > 0 && heap[parentIndex] > heap[index]) {
		swap(heap[parentIndex], heap[index]);
		index = parentIndex;
		parentIndex = (index - 1) / 2;
	}
}

int popHeap(vector<int>& heap) {
	int minElement = heap[0];

	heap[0] = heap[heap.size() - 1];
	heap.pop_back();

	heapifyMinHeap(heap, 0);
	return minElement;
}

void sortNearlySortedArray(vector<int>& arr, int k) {
	vector<int> heap;

	for (int i = 0; i <= k && i < arr.size(); i++) {
		pushHeap(heap, arr[i]);
	}

	int index = 0;

	for (int i = k + 1; i < arr.size(); i++)
	{
		arr[index++] = popHeap(heap);
		pushHeap(heap,  arr[i]);
	}

	while (!heap.empty()) {
		arr[index++] = popHeap(heap);
	}
}

void printArray(const vector<int>& arr) {
	for (int i : arr) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> arr = { 6, 5, 3, 2, 8, 10, 9 };
	int k = 3;

	cout << "Original array: ";
	printArray(arr);

	sortNearlySortedArray(arr, k);

	cout << "Sorted array: ";
	printArray(arr);

	return 0;
}