#include "BasicDataStructure.h"

using namespace std;

template<typename K, typename V>
AVLNode<K, V>::AVLNode(K k, V v) :
	key(k), value(v), left(nullptr), right(nullptr), height(1) {}

template <typename K, typename V>
AVLTreeMap<K, V>::AVLTreeMap() : root(nullptr), size(0) {}

// TODO 
template <typename K, typename V>
AVLTreeMap<K, V>::~AVLTreeMap() {

}


/*
		cur					 left
	   /					/    \
	 left		->      left.r   cur
	   \
		left.r
*/
template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V>::rightRotate(AVLNode<K, V>* cur) {
	AVLNode<K, V>* left = cur->left;
	cur->left = left->right;
	left->right = cur;

	cur->height = 1 + max(
		cur->left ? cur->left->height : 0,
		cur->right ? cur->right->height : 0
	);
	left->height = 1 + max(
		left->left ? left->left->height : 0,
		left->right ? left->right->height : 0
	);
	return left;
}


/*
		cur                 right
		  \               /      \
		 right    ->    cur      right.r
		/				   \
	  right.l			   right.l
*/
template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V>::leftRotate(AVLNode<K, V>* cur) {
	AVLNode<K, V>* right = cur->right;
	cur->right = right->left;
	right->left = cur;

	cur->height = 1 + max(
		cur->left ? cur->left->height : 0,
		cur->right ? cur->right->height : 0
	);
	right->height = 1 + max(
		right->left ? right->left->height : 0,
		right->right ? right->right->height : 0
	);
	return right;
}

/*
1. Calculate the heights of the left and right children. If the height difference (leftHeight - rightHeight) exceeds 1, the node is unbalanced.
2. Left-Heavy Cases:
	LL Case: If the left subtree¡¯s left child height (leftLeftHeight) is greater than or equal to the right child height (leftRightHeight), perform a right rotation on cur.
	LR Case: If the left subtree¡¯s right child is taller, perform a left rotation on cur->left, then a right rotation on cur.
3. Right-Heavy Cases:
	RR Case: If the right subtree¡¯s right child height (rightRightHeight) is greater than or equal to the left child height (rightLeftHeight), perform a left rotation on cur.
	RL Case: If the right subtree¡¯s left child is taller, perform a right rotation on cur->right, then a left rotation on cur.
4. Update cur¡¯s height based on the maximum height of its left and right children after balancing.
*/
template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V>::maintain(AVLNode<K, V>* cur) {
	if (!cur)  return nullptr;

	// Calculate the height of the left and right children
	int leftHeight = cur->left ? cur->left->height : 0;
	int rightHeight = cur->right ? cur->right->height : 0;

	// Check if the current node is unbalanced
	if (abs(leftHeight - rightHeight) > 1) {
		if (leftHeight > rightHeight) {
			// check if it is LL or LR
			int leftLeftHeight = cur->left->left ? cur->left->left->height : 0;
			int leftRightHeight = cur->left->right ? cur->left->right->height : 0;

			if (leftLeftHeight >= leftRightHeight) {
				// LL case: perform a right rotation on cur
				cur = rightRotate(cur);
			}
			else {
				// LR case: first perform a left rotation on cur->left, then a right rotation on cur
				cur->left = leftRotate(cur->left);
				cur = rightRotate(cur);
			}
		}
		else {
			// check if it is RR or RL
			int rightLeftHeight = cur->right->left ? cur->right->left->height : 0;
			int rightRightHeight = cur->right->right ? cur->right->right->height : 0;

			if (rightRightHeight >= rightLeftHeight) {
				// RR case: perform a left rotation on cur
				cur = leftRotate(cur);
			}
			else {
				// RL case: first perform a right rotation on cur->right, then a left rotation on cur
				cur->right = rightRotate(cur->right);
				cur = leftRotate(cur);
			}
		}
	}

	// Update the height of the current node after balancing
	cur->height = 1 + max(
		cur->left ? cur->left->height : 0,
		cur->right ? cur->right->height : 0
	);
	return cur;
}

template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V> ::findLastIndex(const K& key) {
	AVLNode<K, V>* pre = root;
	AVLNode<K, V>* cur = root;

	while (cur) {
		pre = cur;
		if (key == cur->key)
			break;

		else if (key < cur->key)
			cur = cur->left;

		else
			cur = cur->right;
	}
	return pre;
}

template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V> ::findLastNoSmallIndex(const K& key) {
	AVLNode<K, V>* ans = nullptr;
	AVLNode<K, V>* cur = root;

	while (cur) {
		if (key == cur->key) {
			ans = cur;
			break;
		}
		else if (key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return ans;
}

template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V> ::findLastNoBigIndex(const K& key) {
	AVLNode<K, V>* ans = nullptr;
	AVLNode<K, V>* cur = root;

	while (cur) {
		if (key == cur->key) {
			ans = cur;
			break;
		}
		else if (key < cur->key)
			cur = cur->left;
		else {
			ans = cur;
			cur = cur->right;
		}
	}
	return ans;
}

template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V> ::add(AVLNode<K, V>* cur, K& key, V& value) {
	if (!cur) {
		return new AVLNode<K, V>(key, value);
	}
	else {
		if (key < cur->key)
			cur->left = add(cur->left, key, value);
		else
			cur->right = add(cur->right, key, value);
	}

	cur->height = 1 + max(
		cur->left ? cur->left->height : 0,
		cur->right ? cur->right->height : 0
	);
	return maintain(cur);
}


template <typename K, typename V>
AVLNode<K, V>* AVLTreeMap<K, V> ::deleteNode(AVLNode<K, V>* cur, K& key) {
	if (key > cur->key)
		cur->right = deleteNode(cur->right, key);

	else if (key < cur->key)
		cur->left = deleteNode(cur->left, key);

	else {
		if (!cur->left && !cur->right)
			cur = nullptr;

		else if (!cur->left && cur->right)
			cur = cur->right;

		else if (cur->left && !cur->right)
			cur = cur->left;

		else {
			AVLNode<K, V>* des = cur->right;
			while (des) des = des->left;

			cur->right = deleteNode(cur->right, des->key);
			des->left = cur->left;
			des->right = cur->right;
			cur = des;
		}
	}
	if (cur)
		cur->height = 1 + max(
			cur->left ? cur->left->height : 0,
			cur->right ? cur->right->height : 0
		);
	return maintain(cur);
}

template <typename K, typename V>
int AVLTreeMap<K, V>::getSize() const {
	return size;
}

template <typename K, typename V>
bool AVLTreeMap<K, V>::containsKey(const K& key) const {
	if (!key) {
		return false;
	}
	AVLNode<K, V>* lastNode = findLastIndex(key);
	return lastNode && lastNode->key == key;
}


template <typename K, typename V>
void AVLTreeMap<K, V>::put(const K& key, const V& value) {
	if (!key) return;

	AVLNode<K, V>* lastNode = findLastIndex(key);
	if (lastNode && lastNode->key == key)
		lastNode->value = value;

	else {
		size++;
		root = add(root, key, value);
	}
}

template <typename K, typename V>
void AVLTreeMap<K, V>::remove(const K& key) {
	if (!key) return;

	if (containsKey(key)) {
		size--;
		root = deleteNode(root, key);
	}
}

// Retrieves the value associated with a key
template <typename K, typename V>
V* AVLTreeMap<K, V>::get(const K& key) const {
	AVLNode<K, V>* lastNode = findLastIndex(key);
	if (lastNode && lastNode->key == key) {
		return &(lastNode->value);
	}
	return nullptr;
}

// Returns the smallest key in the AVL tree
template <typename K, typename V>
K* AVLTreeMap<K, V>::firstKey() const {
	if (!root)
		return nullptr;
	AVLNode<K, V>* cur = root;
	while (cur->left) {
		cur = cur->left;
	}
	return &(cur->key);
}

// Returns the largest key in the AVL tree
template <typename K, typename V>
K* AVLTreeMap<K, V>::lastKey() const {
	if (!root)
		return nullptr;
	AVLNode<K, V>* cur = root;
	while (cur->right != nullptr) {
		cur = cur->right;
	}
	return &(cur->key);
}

// Finds the largest key less than or equal to the specified key
template <typename K, typename V>
K* AVLTreeMap<K, V>::floorKey(const K& key) const {
	AVLNode<K, V>* lastNoBigNode = findLastNoBigIndex(key);
	return lastNoBigNode ? &(lastNoBigNode->key) : nullptr;
}

template <typename K, typename V>
K* AVLTreeMap<K, V>::ceilingKey(const K& key) const {
	AVLNode<K, V>* lastNoSmallNode = findLastNoSmallIndex(key);
	return lastNoSmallNode ? &(lastNoSmallNode->key) : nullptr;
}