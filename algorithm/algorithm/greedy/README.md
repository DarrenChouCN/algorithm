# Greedy Algorithm
The greedy algorithm makes the optimal choice at each step without considering the future consequences, aiming to reach the global optimum through a series of local optimal decisions. Whether the greedy strategy can yield a global optimal solution depends on the nature of the problem itself.

Problem-Solving Approach:

1. Initial Analysis: Use brute force enumeration to collect data samples and observe their characteristics.
2. Testing Greedy Strategies: Extract potential greedy strategies from the data samples and use a validator (also known as a “comparator” or “oracle”) to test the effectiveness of different strategies.
3. No Need for Over-Proofing: During the strategy exploration phase, do not focus too much on proving correctness. First, experiment with different strategies and validate them through empirical testing.
4. Legitimacy Verification: Once a greedy strategy is identified, it is necessary to prove its validity. When needed, check the "transitivity" of the strategy to ensure it leads to the global optimum.
5. Establish Comparators: Define comparators based on the greedy strategy, which can be used for sorting or maintaining a priority queue to select the local optimal choice at each step.


## Heap Operation
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
```cpp
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
```


## Heap Sort
1. Build the heap (either max-heap or min-heap) from the given array.
2. Repeately swap the last element with the root (the largest or smallest element) and adjust the heap to maintain the heap property.
3. Reduce the size of the heap by 1 (size--), meaning the element at the end is in its final sorted position.
4. Continue this process until the array is sorted.

More Information:
1. The time complexity of heap sort is O(nlogn), which comes from building the heap and performing the sort. The space complexity is O(1), as the sorting process is performed in-place using a constant amount of extra space.
2. If the array is already known in advance, the heap can be built directly by adjusting elements from the end of the array to the beginning. This can optimize the heap-building process, but since the adjustment complexity is still O(nlogn), the overall time complexity remains O(nlogn).
3. The priority queue is essentially a heap structure where the element with the highest priority is placed at the top of the heap. Priority comparisons can be managed by implementing a custom comparator to define the priority of elements.

Time and Space Complexity: O(NlogN), O(1)

```cpp
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
```


## Heap Sort Extension
Given an almost sorted array, where each element's final sorted position will not be more than k positions away from its current position. The task is to sort this array efficiently.

To solve this problem, a min-heap of size k can be used to maintain the order of elements. By continuously adding and removing elements from this heap, the array can be sorted in O(nlogk) time complexity. If k is small, the time complexity can even approach O(n). The goal is to manually implement a min-heap instead of relying on API-based priority queues, as manually maintaining the heap is both educational and practically beneficial in most interview and job situations.

1. Create a min-heap with the first k elements of the array.
2. For the remaining elements, push each new element into the heap and pop the smallest element to place it in its correct position in the sorted array.
3. Once the array has been processed, continue popping the remaining elements from the heap to complete the sorting.

```cpp
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
```

## Activity Selection Problem
Given an array of projects where each project has a start and end time, schedule the projects in such a way that the maximum number of non-overlapping projects can be attended in a meeting room. The strategy involves sorting the projects based on their end times. For each project, if it starts after the previous one ends, it can be included; otherwise, it should be skipped.

Strategies: Sorting by end time, start time, duration.

Expected Results: Generally, sorting by end time will produce the maximum number of non-overlapping projects, confirming that it is the optimal greedy strategy for this problem.

Time and Space Complexity: O(nlogn) and O(n)

```cpp
// Comparator for sorting by end time
bool compareByEnd(const Project& a, const Project& b) {
	// Comparator for sorting by duration
	//return (a.end - a.start) < (b.end - b.start);

	// Comparator for sorting by start time
	//return a.start < b.start;

	return a.end < b.end;
}

int maxEvents(vector<Project>& projects, bool (*compare)(const Project&, const Project&)) {
	// Sort projects by end time using the comparator
	sort(projects.begin(), projects.end(), compare);

	int count = 0, lastEndTime = 0;
	for (const auto& project : projects)
	{
		if (project.start >= lastEndTime) {
			count++;
			lastEndTime = project.end;
		}
	}
	return count;
}
```

## Gold Bar Cutting Problem
You have a gold bar of length n, and you want to divide it into smaller pieces. Each time you cut the gold bar, the cost is equal to the length of the gold bar you are cutting. The goal is to split the gold bar into multiple pieces in such a way that the total cost of all the cuts is minimized.

Huffman-like Greedy Algorithm
To minimize the total cost of cutting the gold bar, the strategy is to always combine the two smallest pieces of gold at each step. This ensures that the larger pieces are cut later, reducing the overall cost.

Time and Space Complexity: O(nlogn) and O(n)

```cpp
int minCostToCutGoldBar(const vector<int>& lengths) {
	priority_queue<int, vector<int>, greater<int>> minHeap(lengths.begin(), lengths.end());

	int totalCost = 0;

	while (minHeap.size() > 1) {
		int first = minHeap.top();
		minHeap.pop();
		int second = minHeap.top();
		minHeap.pop();

		int cost = first + second;
		totalCost += cost;

		minHeap.push(cost);
	}

	return totalCost;
}
```

## Profit Maximization
You are given a set of projects, each with an associated cost and profit. The goal is to maximize your total amount of money by selecting up to k projects. You start with an initial capital m, and each time you select a project, you can only choose one that you can afford with your current capital. The aim is to complete at most k projects and achieve the maximum final capital.

Greedy with Priority Queues
A min-heap to manage projects by their cost and a max-heap to select the project with the highest profit among the projects.
The maximum profit is inserted into the max-heap. Projects are initially added to a min-heap, prioritized by their cost in ascending order. A loop runs with the maximum limit being the number of projects that can be selected. In each iteration, the top element of the min-heap is checked to see if its cost is less than or equal to the current available capital. If the condition is met, the project is moved from the min-heap (smallest cost) to the max-heap (maximum profit). Then, the top element of the max-heap (maximum profit) is added to the current capital, and it is removed from the heap. This process repeats until no more valid projects can be selected.

Time and Space Complexity: O(nlogn) and O(n)

```cpp
int maximizeCapital(int k, int initialCapital, vector<int>& costs, vector<int>& profits) {
	priority_queue<pair<int, int>, vector<pair<int, int>>,
		greater<pair<int, int>>> minCostHeap;

	priority_queue<int> maxProfitHeap;

	for (int i = 0; i < costs.size(); i++)
		minCostHeap.push({ costs[i],profits[i] });

	int currentCapital = initialCapital;

	for (int i = 0; i < k; i++)
	{
		while (!minCostHeap.empty() && minCostHeap.top().first <= currentCapital) {
			maxProfitHeap.push(minCostHeap.top().second);
			minCostHeap.pop();
		}

		if (maxProfitHeap.empty()) break;

		currentCapital += maxProfitHeap.top();
		maxProfitHeap.pop();
	}
	return currentCapital;
}
```