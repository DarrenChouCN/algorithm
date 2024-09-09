# Master Theorem
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


# Merge Sort
Merge Sort is a fundamental recursive algorithm with the following core ideas:

1. The overall process is a simple recursion: sort the left side, sort the right side, and then merge them to make the whole array ordered, using an external sorting method.
2. The time complexity is lower than O(n^2) because, compared to selection or insertion sort, merge sort reduces the number of comparisons. This is achieved by comparing already sorted subarrays, rather than individual elements, as the recursion progresses to larger portions of the array.
3. According to the application of the Master Theorem in merge sort, a=2, b=2, and d=1. Thus, the time complexity is O(n^d*(logN)), which simplifies to O(NlogN). Since additional space is required to store temporary variables during merging, the space complexity is O(n).

Time and Space Complexity: O(NlogN), O(n)

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

# Small Sum
In an array, for each element, find the sum of all the numbers to its left that are smaller than the current number.

By utilizing the merge sort technique, the comparisons between individual elements can be transformed into range-based comparisons, reducing the overall number of comparisons and improving time complexity.

1. Use merge sort to recursively divide the array into two halves.
2. During the merge step, calculate the small sum by identifying the elements in the left subarray that are smaller than those in the right subarray.
3. Accumulate the small sum during the merge process.
4. Return the total small sum after the complete merging process.

Time and Space Complexity: O(NlogN), O(n)
		
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


# Reverse Pairs
The reverse pairs Problem is an extension of the merge sort algorithm. The task is to count and output all the reverse pairs in an array. A reverse pair is defined as a pair of elements where the left element is greater than the right element.

The reverse pairs problem is an extension of the merge sort algorithm. During the sorting process, when an element in the left half is found to be greater than an element in the right half, the number of reverse pairs is calculated by subtracting the indices. Specifically, the number of reverse pairs is the difference in indices between the current element in the left half and the right half. Each such reverse pair is then printed as it is discovered.

Time and Space Complexity: O(NlogN), O(n)

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

# Partitioning an Array
The goal is to partition an array based on a given pivot value, such that all elements smaller than the pivot are placed on the left side of the array, and all elements greater than the pivot are placed on the right side.

Use a two-pointer or one-pointer approach to rearrange the elements, placing smaller elements to the left and larger elements to the right. This process involves traversing the array once and swapping elements to achieve the partition.

Time and Space Complexity: O(N), O(1)

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

# Dutch National Flag
The Dutch National Flag problem involves partitioning an array into three parts based on a given pivot value:

1. Elements less than the pivot go to the left.
2. Elements equal to the pivot stay in the middle.
3. Elements greater than the pivot go to the right.

The solution uses a three-pointer approach.

1. The left pointer tracks the boundary of elements smaller than the pivot.
2. The right pointer tracks the boundary of elements larger than the pivot.
3. The current pointer traverses the array.

Time and Space Complexity: O(1)

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

# Quick Sorting Optimization
1. Three-way partitioning (Dutch National Flag problem): This optimization reduces redundant comparisons and recursion for elements that are equal to the pivot. For arrays with many equal elements, this optimization significantly improves efficiency.
2. Random pivot selection: This strategy avoids the potential imbalance that could occur when using a fixed pivot, which might lead to worst-case performance O(N^2). By selecting the pivot randomly, more balanced partitions are likely to occur overall, maintaining a stable time complexity of O(nlogn).

Explanation:

1. The recursive QuickSort algorithm now integrates both random pivot selection and three-way partitioning, which improves the performance when handling arrays with duplicate elements and ensures more balanced partitions.
2. The average time complexity remains O(nlogn), but this combined version performs better when handling arrays with many duplicates due to fewer redundant comparisons.

Time and Space Complexity: O(NlogN), O(N)

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