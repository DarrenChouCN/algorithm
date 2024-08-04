/*
Merge Sorted Array

You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
*/

/*
Use a two-pointer approach, iterating from the end of both arrays and placing the larger element at the end of the merged array in 'nums1'.

1. Create three pointers:
	p1 for traversing nums1 from the end of its valid elements, initially pointing to the (m-1)th element.
	p2 for traversing nums2 from the end, initially pointing to the (n-1)th element.
	tail for indicating the current position in nums1 where the next largest element should be placed, initially pointing to the (m+n-1)th element.

2. Start a loop with the condition that both arrays have not been fully traversed. Compare the elements pointed to by p1 and p2. Assign the larger element to the position indicated by tail in nums1, and move the corresponding pointer (p1 or p2) backward. Move tail backward as well.

3. If p2 still has remaining elements after the loop ends, copy all remaining elements from nums2 to nums1.

Time Complexity: O(m+n)
Space Complexity: O(1)
*/

#include <iostream>
#include <vector>

using namespace std;

class MergeSortedArray {
public:
	void mergeSortedArray(vector<int> &nums1, int m, vector<int> &nums2, int n) {
		int p1 = m - 1;
		int p2 = n - 1;
		int tail = m + n - 1;

		while (p1 >= 0 || p2 >= 0)
		{
			if (p1 == -1)
			{
				nums1[tail--] = nums2[p2--];
			}
			else if (p2 == -1) {
				nums1[tail--] = nums1[p1--];
			}
			else if (nums1[p1] > nums2[p2]) {
				nums1[tail--] = nums1[p1--];
			}
			else {
				nums1[tail--] = nums2[p2--];
			}
		}
	}
};

int main() {

	MergeSortedArray solution;

	vector<int> nums1 = { 1, 2, 3, 0, 0, 0 };
	int m = 3;
	vector<int> nums2 = { 2, 5, 6 };
	int n = 3;

	solution.mergeSortedArray(nums1, m, nums2, n);

	cout << "Merged array: ";
	for (int num : nums1) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}