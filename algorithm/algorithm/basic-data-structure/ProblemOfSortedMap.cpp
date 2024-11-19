#include <vector>
#include <unordered_set>
#include <iostream>
#include <stdexcept>
#include <set>

using namespace std;

/*
Sorted Map 
Traditional arrays (e.g., Java's ArrayList and C++'s vector) are implemented as dynamic memory blocks. While they offer fast random access with  O(1) complexity, their insertion and deletion operations require shifting elements, resulting in  O(n) complexity. Linked lists (e.g., Java's LinkedList and C++'s list) allow  O(1) insertion and deletion at the head or tail, but random access and modifications in the middle still have  O(n) complexity. These limitations make traditional arrays and linked lists inefficient in scenarios with frequent insertions, deletions, or dynamic ordering.

In contrast, ordered sets (e.g., AVL trees, red-black trees, and skip lists) dynamically maintain sorted order, enabling efficient operations like insertion, deletion, and search with  O(logn) complexity. They excel in scenarios requiring frequent data updates, such as sliding window problems (e.g., calculating dynamic medians), dynamic range queries (e.g., finding the k-th smallest element or calculating range sums), real-time sorting, and ranking updates. By avoiding extra sorting or traversal overhead, ordered sets significantly improve performance in these cases.

In modern programming languages, ordered sets are implemented in various forms. Java offers TreeMap and TreeSet, based on red-black trees, which support dynamic insertion, deletion, and sorting. C++ provides std::set, std::map, and their multi-key counterparts (std::multiset and std::multimap). Python provides SortedDict and SortedSet through the sortedcontainers library, while PHP arrays maintain partial order by preserving insertion sequences. These built-in structures simplify the use of ordered sets, eliminating the need to manually implement balanced trees.

In some high-level languages, data structures use natural insertion order as an implicit key to build ordered sets or trees. Regardless of how nodes are rotated or adjusted internally, the insertion order remains unchanged. This is achieved by storing additional metadata, such as insertion timestamps or sequence numbers, in each node to maintain the relative order of insertion. This feature effectively combines dynamic ordering with natural sequence preservation, making it highly suitable for scenarios involving frequent insertions and deletions.

Modern programming languages widely adopt this approach. For example, Python's dict and OrderedDict maintain insertion order; PHP's arrays combine linked lists and hash tables to preserve order; Java's LinkedHashMap and C++'s boost::multi_index_container offer similar functionality. These tools are particularly useful in applications like log management, ranking updates, and scenarios requiring a combination of order preservation and dynamic operations.
*/

/*
Count of Range Sum

https://leetcode.com/problems/count-of-range-sum/
Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive. Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.

Objective: To count the number of subarrays where a≤sum[i:j]≤b.

Core Idea: Use the prefix sum array to efficiently compute subarray sums, and further enhance performance by leveraging the dynamic insertion and range query capabilities of an ordered set.

Details:
1. The prefix sum formula sum[i:j]=prefix[j]−prefix[i−1] can be transformed into the inequality prefix[i−1]∈[prefix[j]−b,prefix[j]−a].
2. prefix[i−1] represents the cumulative sum of the first i−1 elements. Counting how many such prefix[i−1] values fall within the specified range corresponds directly to the number of valid subarrays.
3. Extend the structure of the ordered set by adding a size parameter to each node, representing the count of elements within that subtree that satisfy the conditions. During the traversal and insertion of elements, dynamically update the size of the relevant nodes based on the properties of the ordered set.
4. After traversing the prefix sum array, the accumulated results represent the total number of subarrays satisfying the conditions.

Time Complexity: The overall complexity is O(nlogn), encompassing the construction of the prefix sum array and the management of the ordered set.
*/
class CountRangeSum {
public:
	int countRangeSum(const vector<int>& nums, int lower, int upper) {
		SizeBalancedTreeSet treeSet;
		long sum = 0;
		int ans = 0;

		treeSet.add(0);

		for (int num : nums) {
			sum += num;

			// Calculate how many prefix sums fall within [sum - upper, sum - lower]
			long a = treeSet.lessKeySize(sum - lower + 1); // Prefix sums < (sum - lower + 1)
			long b = treeSet.lessKeySize(sum - upper);     // Prefix sums <= (sum - upper)

			ans += a - b;

			treeSet.add(sum);
		}

		return ans;
	}

	class SizeBalancedTreeSet {
	private:
		struct SBTNode {
			long key;
			long size;
			long all;
			SBTNode* left;
			SBTNode* right;

			SBTNode(long k) : key(k), size(1), all(1), left(nullptr), right(nullptr) {}
		};

		SBTNode* root;
		unordered_set<long> set;

		SBTNode* rightRotate(SBTNode* cur) {
			if (!cur || !cur->left)
				return cur;
			long same = cur->all - (cur->left ? cur->left->all : 0) - (cur->right ? cur->right->all : 0);
			SBTNode* leftNode = cur->left;
			cur->left = leftNode->right;
			leftNode->right = cur;
			leftNode->size = cur->size;
			cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
			leftNode->all = cur->all;
			cur->all = (cur->left ? cur->left->all : 0) + (cur->right ? cur->right->all : 0) + same;
			return leftNode;
		}

		SBTNode* leftRotate(SBTNode* cur) {
			if (!cur || !cur->right)
				return cur;
			long same = cur->all - (cur->left ? cur->left->all : 0) - (cur->right ? cur->right->all : 0);
			SBTNode* rightNode = cur->right;
			cur->right = rightNode->left;
			rightNode->left = cur;
			rightNode->size = cur->size;
			cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
			rightNode->all = cur->all;
			cur->all = (cur->left ? cur->left->all : 0) + (cur->right ? cur->right->all : 0) + same;
			return rightNode;
		}

		SBTNode* maintain(SBTNode* cur) {
			if (!cur) return nullptr;

			long leftSize = cur->left ? cur->left->size : 0;
			long leftLeftSize = cur->left && cur->left->left ? cur->left->left->size : 0;
			long leftRightSize = cur->left && cur->left->right ? cur->left->right->size : 0;
			long rightSize = cur->right ? cur->right->size : 0;
			long rightLeftSize = cur->right && cur->right->left ? cur->right->left->size : 0;
			long rightRightSize = cur->right && cur->right->right ? cur->right->right->size : 0;

			if (leftLeftSize > rightSize) {
				cur = rightRotate(cur);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			else if (leftRightSize > rightSize) {
				cur->left = leftRotate(cur->left);
				cur = rightRotate(cur);
				cur->left = maintain(cur->left);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			else if (rightRightSize > leftSize) {
				cur = leftRotate(cur);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			else if (rightLeftSize > leftSize) {
				cur->right = rightRotate(cur->right);
				cur = leftRotate(cur);
				cur->left = maintain(cur->left);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			return cur;
		}

		SBTNode* add(SBTNode* cur, long key, bool contains) {
			if (!cur) {
				return new SBTNode(key);
			}
			cur->all++;
			if (key == cur->key)
				return cur;

			else {
				if (!contains)
					cur->size++;

				if (key < cur->key)
					cur->left = add(cur->left, key, contains);

				else
					cur->right = add(cur->right, key, contains);

				return maintain(cur);
			}
		}

	public:
		SizeBalancedTreeSet() : root(nullptr) {}

		void add(long sum) {
			bool contains = set.find(sum) != set.end();
			root = add(root, sum, contains);
			set.insert(sum);
		}

		long lessKeySize(long key) {
			SBTNode* cur = root;
			long ans = 0;
			while (cur) {
				if (key == cur->key) {
					return ans + (cur->left ? cur->left->all : 0);
				}
				else if (key < cur->key) {
					cur = cur->left;
				}
				else {
					ans += cur->all - (cur->right ? cur->right->all : 0);
					cur = cur->right;
				}
			}
			return ans;
		}

		long moreKeySize(long key) {
			return root ? (root->all - lessKeySize(key + 1)) : 0;
		}
	};
};

/*
Sliding Window Median (Sorted Map)

https://leetcode.com/problems/sliding-window-median/description/

Using multiset (based on a red-black tree), the sliding window is managed by maintaining an ordered set of size k. Initially, the first k elements are added to the multiset to establish the initial window. Then, for each subsequent element, a new element is inserted into the multiset, the median is calculated, and the oldest element is removed to simulate the sliding window behavior. The median is efficiently retrieved due to the ordered nature of the multiset.

Time Complexity and Space Complexity: O(nlogk) and O(k)
*/

// Node structure for maintaining the index and value in the sliding window
struct Node {
	int index;
	int value;

	Node(int i, int v) : index(i), value(v) {}

	// Custom comparator for maintaining order in the multiset
	bool operator<(const Node& other) const {
		return value != other.value ? value < other.value : index < other.index;
	}
};

// Main function to calculate medians of all sliding windows
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
	multiset<Node> window;  // Multiset to maintain the sorted sliding window
	vector<double> result; 

	for (int i = 0; i < k - 1; ++i) {
		window.insert(Node(i, nums[i]));
	}

	for (int i = k - 1; i < nums.size(); ++i) {
		window.insert(Node(i, nums[i]));

		// Find the median
		auto mid = next(window.begin(), k / 2); // Middle iterator
		if (k % 2 == 0) { // Even size: average of two middle elements
			auto mid_prev = prev(mid);
			result.push_back(((double)mid->value + (double)mid_prev->value) / 2);
		}
		else { // Odd size: single middle element
			result.push_back((double)mid->value);
		}

		// Remove the element that slides out of the window
		window.erase(window.find(Node(i - k + 1, nums[i - k + 1])));
	}

	return result;
}

int mainMedianSlidingWindow() {
	vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
	int k = 3;
	vector<double> result = medianSlidingWindow(nums, k);

	for (double median : result) {
		cout << median << " ";
	}

	return 0;
}
