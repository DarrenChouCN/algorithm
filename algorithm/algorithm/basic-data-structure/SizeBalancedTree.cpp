#include <iostream>
#include <string>
#include "BasicDataStructure.h"

using namespace std;

/*
Difference between Size Balanced Tree and AVL Tree:
A Size Balanced (SB) Tree is a self-balancing binary search tree that maintains balance by ensuring size constraints across its subtrees, rather than strict height constraints like in an AVL tree. While AVL trees focus on keeping the tree height balanced to minimize path length, SB trees balance by comparing subtree sizes and performing rotations only when the size imbalance exceeds a certain threshold. This typically results in fewer rotations and slightly faster insertion/deletion operations in some cases, though SB trees may not achieve as strict height balance as AVL trees.

Time and Space Complexity of SB Tree:
The time complexity for search, insertion, and deletion operations in an SB Tree is O(logn) on average, similar to other balanced trees like AVL and Red-Black trees. However, due to its size-based balancing, it may experience slightly better performance in practice under certain workloads. The space complexity of an SB Tree is O(n), as it stores one node per element plus a small amount of additional storage for balancing metadata.
*/

// Right Rotate
template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::rightRotate(
	SBTNode<K, V, Comparator>* cur) {
	SBTNode<K, V, Comparator>* leftNode = cur->left;
	cur->left = leftNode->right;
	leftNode->right = cur;
	leftNode->size = cur->size;
	cur->size = getNodeSize(cur);
	return leftNode;
}

// Left Rotate
template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::leftRotate(
	SBTNode<K, V, Comparator>* cur) {
	SBTNode<K, V, Comparator>* rightNode = cur->right;
	cur->right = rightNode->left;
	rightNode->left = cur;
	rightNode->size = cur->size;
	cur->size = getNodeSize(cur);
	return rightNode;
}

// Recursively Maintain
template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::maintain(
	SBTNode<K, V, Comparator>* cur) {
	if (!cur) return nullptr;

	int leftSize = cur->left ? cur->left->size : 0;
	int leftLeftSize = (cur->left && cur->left->left) ? cur->left->left->size : 0;
	int leftRightSize = (cur->left && cur->left->right) ? cur->left->right->size : 0;

	int rightSize = cur->right ? cur->right->size : 0;
	int rightLeftSize = (cur->right && cur->right->left) ? cur->right->left->size : 0;
	int rightRightSize = (cur->right && cur->right->right) ? cur->right->right->size : 0;

	// LL case
	if (leftLeftSize > rightSize) {
		cur = rightRotate(cur);
		cur->right = maintain(cur->right);
		cur = maintain(cur);
	}
	//LR case
	else if (leftRightSize > rightSize) {
		cur->left = leftRotate(cur->left);
		cur = rightRotate(cur);
		cur->left = maintain(cur->left);
		cur->right = maintain(cur->right);
		cur = maintain(cur);
	}
	//RR case
	else if (rightRightSize > leftSize) {
		cur = leftRotate(cur);
		cur->left = maintain(cur->left);
		cur = maintain(cur);
	}
	//RL case
	else if (rightLeftSize > leftSize) {
		cur->right = rightRotate(cur->right);
		cur = leftRotate(cur);
		cur->left = maintain(cur->left);
		cur->right = maintain(cur->right);
		cur = maintain(cur);
	}

	return cur;
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::findLastIndex(
	const K& key) {
	SBTNode<K, V, Comparator>* pre = nullptr;
	SBTNode<K, V, Comparator>* cur = root;

	while (cur) {
		pre = cur;
		if (!comp(key, cur->key) && !comp(cur->key, key))
			break;
		else if (comp(key, cur->key))
			cur = cur->left;
		else
			cur = cur->right;
	}
	return pre;
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::findLastNoSmallIndex(
	const K& key) {
	SBTNode<K, V, Comparator>* ans = nullptr;
	SBTNode<K, V, Comparator>* cur = root;

	while (cur) {
		if (!comp(key, cur->key) && !comp(cur->key, key)) {
			ans = cur;
			break;
		}
		else if (comp(key, cur->key)) {
			ans = cur;
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	return ans;
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::findLastNoBigIndex(
	const K& key) {
	SBTNode<K, V, Comparator>* ans = nullptr;
	SBTNode<K, V, Comparator>* cur = root;

	while (cur) {
		if (!comp(key, cur->key) && !comp(cur->key, key)) {
			ans = cur;
			break;
		}
		else if (comp(key, cur->key)) {
			cur = cur->left;
		}
		else {
			ans = cur;
			cur = cur->right;
		}
	}
	return ans;
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::add(
	SBTNode<K, V, Comparator>* cur, const K& key, const V& value) {
	if (!cur) {
		return new SBTNode<K, V, Comparator>(key, value);
	}
	else {
		cur->size++;
		if (cur->comp(key, cur->key))
			cur->left = add(cur->left, key, value);
		else
			cur->right = add(cur->right, key, value);
	}

	return maintain(cur);
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::remove(
	SBTNode<K, V, Comparator>* cur, const K& key) {
	if (!cur) return nullptr;

	cur->size--;
	if (comp(cur->key,key)) {
		cur->right = remove(cur->right, key);
	}
	else if (comp(key, cur->key)) {
		cur->left = remove(cur->left, key);
	}
	else {
		if (!cur->left && !cur->right) { // Case 1: No children
			delete cur;
			cur = nullptr;
		}
		else if (!cur->left) { // Case 2: Only right child
			SBTNode<K, V, Comparator>* temp = cur;
			cur = cur->right;
			delete temp;
		}
		else if (!cur->right) { // Case 3: Only left child
			SBTNode<K, V, Comparator>* temp = cur;
			cur = cur->left;
			delete temp;
		}
		// Case 4: Both children exist, Find the in-order successor (des) in the right subtree.
		else {
			SBTNode<K, V, Comparator>* pre = nullptr;
			SBTNode<K, V, Comparator>* des = cur->right;
			des->size--;

			while (des->left) {
				pre = des;
				des = des->left;
				des->size--;
			}
			if (pre) {
				pre->left = des->right;
				des->right = cur->right;
			}

			des->left = cur->left;
			des->size = getNodeSize(des);
			delete cur;
			cur = des;
		}
	}

	if (cur) cur = maintain(cur);
	return cur;
}

template <typename K, typename V, typename Comparator>
SBTNode<K, V, Comparator>* SizeBalancedTreeMap<K, V, Comparator>::getIndex(
	SBTNode<K, V, Comparator>* cur, int kth) {
	if (!cur) return nullptr;

	int leftSize = cur->left ? cur->left->size : 0;
	if (kth == leftSize + 1)
		return cur;
	else if (kth <= leftSize)
		return getIndex(cur->left, kth);
	else
		return getIndex(cur->right, kth - leftSize - 1);
}

template<typename K, typename V, typename Comparator>
int SizeBalancedTreeMap<K, V, Comparator>::size() const {
	return root ? root->size : 0;
}

template<typename K, typename V, typename Comparator>
bool SizeBalancedTreeMap<K, V, Comparator>::containsKey(const K& key) {
	//if (!key) throw invalid_argument("Invalid parameter.");

	SBTNode<K, V, Comparator>* lastNode = findLastIndex(key);
	return lastNode && !comp(key, lastNode->key) && !comp(lastNode->key, key);
}

template<typename K, typename V, typename Comparator>
void SizeBalancedTreeMap<K, V, Comparator>::put(const K& key, const V& value) {
	//if (!key) throw invalid_argument("Invalid parameter.");

	SBTNode<K, V, Comparator>* lastNode = findLastIndex(key);
	if (lastNode && !comp(key, lastNode->key) && !comp(lastNode->key, key))
		lastNode->value = value;
	else
		root = add(root, key, value);
}

template<typename K, typename V, typename Comparator>
void SizeBalancedTreeMap<K, V, Comparator>::remove(const K& key) {
	//if (!key) throw invalid_argument("Invalid parameter.");

	if (containsKey(key))
		root = remove(root, key);
}

template<typename K, typename V, typename Comparator>
K SizeBalancedTreeMap<K, V, Comparator>::getIndexKey(int index) {
	if (index < 0 || index >= size())
		throw invalid_argument("Invalid parameter.");

	SBTNode<K, V, Comparator>* node = getIndex(root, index + 1);
	return node ? node->key : K();
}

template<typename K, typename V, typename Comparator>
V SizeBalancedTreeMap<K, V, Comparator>::get(const K& key) {
	//if (!key) throw invalid_argument("Invalid parameter.");

	SBTNode<K, V, Comparator>* lastNode = findLastIndex(key);
	if (lastNode && !comp(key, lastNode->key) && !comp(lastNode->key, key))
		return lastNode->value;
	else
		return V();
}

template<typename K, typename V, typename Comparator>
K SizeBalancedTreeMap<K, V, Comparator>::firstKey() {
	if (!root) return K();

	SBTNode<K, V, Comparator>* cur = root;
	while (cur->left) {
		cur = cur->left;
	}
	return cur->key;
}

template<typename K, typename V, typename Comparator>
K SizeBalancedTreeMap<K, V, Comparator>::lastKey() {
	if (!root) return K();

	SBTNode<K, V, Comparator>* cur = root;
	while (cur->right) {
		cur = cur->right;
	}
	return cur->key;
}

// Returns the largest key less than or equal to the specified key
template<typename K, typename V, typename Comparator>
K SizeBalancedTreeMap<K, V, Comparator>::floorKey(const K& key) {
	SBTNode<K, V, Comparator>* lastNoBigNode = findLastNoBigIndex(key);
	return lastNoBigNode ? lastNoBigNode->key : K();
}

// Returns the smallest key greater than or equal to the specified key
template<typename K, typename V, typename Comparator>
K SizeBalancedTreeMap<K, V, Comparator>::ceilingKey(const K& key) {
	SBTNode<K, V, Comparator>* lastNoSmallNode = findLastNoSmallIndex(key);
	return lastNoSmallNode ? lastNoSmallNode->key : K();
}


// Function to get a string of spaces
string getSpace(int num) {
	string space = " ";
	string buf;
	for (int i = 0; i < num; i++) {
		buf += space;
	}
	return buf;
}

// Recursive function to print the tree in an in-order format
void printInOrder(SBTNode<string, int>* head, int height, string to, int len) {
	if (!head) {
		return;
	}
	printInOrder(head->right, height + 1, "v", len);
	string val = to + "(" + head->key + "," + to_string(head->value) + ")" + to;
	int lenM = val.length();
	int lenL = (len - lenM) / 2;
	int lenR = len - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height * len) + val << endl;
	printInOrder(head->left, height + 1, "^", len);
}

// Function to print the entire tree structure
void printAll(SBTNode<string, int>* head) {
	cout << "Binary Tree:" << endl;
	printInOrder(head, 0, "H", 17);
	cout << endl;
}

struct Apple {
	int size;
	Apple() : size(0) {}
	Apple(int s) : size(s) {}
};

struct AppleComparator {
	bool operator()(const Apple& a, const Apple& b) const {
		return a.size < b.size;  // Comparison based on the `size` member of `Apple`
	}
};

int mainSizeBalancedTree() {
	SizeBalancedTreeMap<Apple, int, AppleComparator> sbt;

	// Insert Apple objects with various sizes
	sbt.put(Apple(10), 1);
	sbt.put(Apple(20), 2);
	sbt.put(Apple(5), 3);
	sbt.put(Apple(15), 4);
	sbt.put(Apple(25), 5);
	sbt.put(Apple(3), 6);
	sbt.put(Apple(8), 7);
	sbt.put(Apple(30), 8);

	// Test retrieval with get
	cout << "Value for Apple(10): " << sbt.get(Apple(10)) << endl;
	cout << "Value for Apple(20): " << sbt.get(Apple(20)) << endl;
	cout << "Value for Apple(5): " << sbt.get(Apple(5)) << endl;

	// Test firstKey and lastKey
	cout << "First Key: Apple(" << sbt.firstKey().size << ")" << endl;
	cout << "Last Key: Apple(" << sbt.lastKey().size << ")" << endl;

	// Test floorKey and ceilingKey
	cout << "Floor Key of Apple(18): Apple(" << sbt.floorKey(Apple(18)).size << ")" << endl;
	cout << "Ceiling Key of Apple(18): Apple(" << sbt.ceilingKey(Apple(18)).size << ")" << endl;

	cout << "Floor Key of Apple(9): Apple(" << sbt.floorKey(Apple(9)).size << ")" << endl;
	cout << "Ceiling Key of Apple(9): Apple(" << sbt.ceilingKey(Apple(9)).size << ")" << endl;

	// Test remove
	sbt.remove(Apple(10));
	cout << "After removing Apple(10), Value for Apple(10): " << sbt.get(Apple(10)) << endl;
	sbt.remove(Apple(20));
	cout << "After removing Apple(20), Value for Apple(20): " << sbt.get(Apple(20)) << endl;

	// Test firstKey and lastKey after removals
	cout << "First Key after removals: Apple(" << sbt.firstKey().size << ")" << endl;
	cout << "Last Key after removals: Apple(" << sbt.lastKey().size << ")" << endl;

	return 0;
}

