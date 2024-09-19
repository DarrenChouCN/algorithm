#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include "../common.h"

using namespace std;

// Time and Space Complexity: O(n) and O(h)
void preorder1(TreeNode* root) {
	if (root == nullptr) return;

	cout << root->val << " ";

	preorder1(root->left);

	preorder1(root->right);
}

void inorder1(TreeNode* root) {
	if (root == nullptr) return;

	inorder1(root->left);

	cout << root->val << " ";

	inorder1(root->right);
}

void postorder1(TreeNode* root) {
	if (root == nullptr) return;

	postorder1(root->left);

	postorder1(root->right);

	cout << root->val << " ";
}

// Time and Space Complexity: O(n) and O(n)
void levelOrder(TreeNode* root) {
	if (root == nullptr) return;

	queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();

		cout << node->val << " ";

		if (node->left) q.push(node->left);

		if (node->right) q.push(node->right);
	}
}

// Time and Space Complexity: O(n) and O(h)
void preorder2(TreeNode* root) {
	if (root == nullptr) return;

	stack<TreeNode*> s;
	s.push(root);

	while (!s.empty()) {
		TreeNode* node = s.top();
		s.pop();

		cout << node->val << " ";

		if (node->right) s.push(node->right);

		if (node->left) s.push(node->left);
	}
}

void inorder2(TreeNode* root) {
	stack<TreeNode*> s;
	TreeNode* current = root;

	while (current != nullptr || !s.empty()) {
		while (current != nullptr) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();

		cout << current->val << " ";

		current = current->right;
	}
}

void postorder2(TreeNode* root) {
	if (root == nullptr) return;

	stack<TreeNode*> s;
	TreeNode* current = root;
	TreeNode* lastVisited = nullptr;

	while (current != nullptr || !s.empty()) {
		while (current != nullptr) {
			s.push(current);
			current = current->left;
		}

		TreeNode* topNode = s.top();

		if (topNode->right != nullptr && topNode->right != lastVisited) {
			current = topNode->right;
		}
		else {
			cout << topNode->val << " ";
			s.pop();
			lastVisited = topNode;
		}
	}
}


/*
Max Width Of Binary Tree

This method for calculating the maximum width fundamentally utilizes the properties of a binary tree, specifically the formulas for calculating the indices of child nodes, and uses these indices to compute the width of the current level. It keeps track of the maximum width using a variable. Each time it traverses the tree, all nodes of the current level are added to the queue, and the size is predetermined. Thus, the number of nodes dequeued matches the number of nodes in the current level.

Time and Space Complexity: O(n) and O(n)
*/
int maxWidthOfBinaryTree(TreeNode* root) {
	if (root == nullptr) return 0;

	queue<pair<TreeNode*, int>> q;
	q.push({ root, 0 });
	int maxWidth = 0;

	while (!q.empty()) {
		int size = q.size();
		int left = q.front().second;
		int right = q.back().second;

		maxWidth = max(maxWidth, right - left + 1);

		for (int i = 0; i < size; ++i) {
			pair<TreeNode*, int> node = q.front();
			q.pop();
			int index = node.second;

			if (node.first->left) {
				q.push({ node.first->left, 2 * index });
			}
			if (node.first->right) {
				q.push({ node.first->right, 2 * index + 1 });
			}
		}
	}

	return maxWidth;
}


/*
In a BST, the left child is smaller than the parent node, so the maximum value allowed for the left subtree should be the parent node's value. Similarly, the right child is larger than the parent node, so the minimum value allowed for the right subtree should be the parent node's value. This is why, during the recursive validation, the maximum value for the left subtree is updated to the parent node's value, and the minimum value for the right subtree is updated to the parent node's value.

Time and Space Complexity: O(n) and O(h)
*/
bool isValidBST1(TreeNode* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
	if (root == nullptr) return true;

	if (root->val <= minVal || root->val >= maxVal)
		return false;

	return isValidBST1(root->left, minVal, root->val) && isValidBST1(root->right, root->val, maxVal);
}


/*
In a BST, the left child is smaller than the parent node, and the parent node is smaller than the right child. During an in-order traversal, the sequence is left -> root -> right, meaning that the nodes visited earlier should be smaller. Therefore, prevVal must be less than current->val. If at any point prevVal is greater than or equal to current->val, it indicates that the tree is not a BST.

Time and Space Complexity: O(n) and O(h)
*/
bool isValidBST2(TreeNode* root) {
	if (root == nullptr) return true;

	stack<TreeNode*> s;
	TreeNode* current = root;
	long long prevVal = LLONG_MIN;

	while (current != nullptr || !s.empty()) {
		while (current != nullptr) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();

		if (prevVal >= current->val) return false;

		prevVal = current->val;
		current = current->right;
	}

	return true;
}


/*
Is Complete and Full Binary Tree
This implementation uses a single traversal of the binary tree with an O(n) time complexity to check if the tree is a complete binary tree, a full binary tree, and to calculate the tree's height, while also tracking the index of each node.

1. BFS: A queue is used to perform a level-order traversal (BFS), visiting each node exactly once, maintaining an O(n) complexity.
2. Multi-Tasking:
	a. During traversal, the index of each node is calculated. By comparing the last node's index with totalNodes - 1, it is possible to determine if the tree is a complete binary tree.
	b. The tree's height is calculated in the BFS by counting the levels. Using this height, the total nodes are compared with 2^h−1 to verify if the tree is a full binary tree.
	c. The height is incremented each time a new level is processed.
	d. The properties of a binary tree are used to track indices, assisting in verifying completeness.

This approach combines multiple checks (completeness, fullness, and height) into a single traversal, reducing redundant computations.

Time and Space Complexity: O(n) and O(n)
*/
pair<bool, bool> isCompleteAndFullBT(TreeNode* root) {
	if (root == nullptr) return { true,true };

	queue<pair<TreeNode*, int>> q;
	q.push({ root,0 });

	int totalNodes = 0, height = 0, lastIndex = 0;

	while (!q.empty()) {
		int levelSize = q.size();
		height++;

		for (int i = 0; i < levelSize; i++)
		{
			TreeNode* current = q.front().first;
			int index = q.front().second;

			q.pop();

			totalNodes++;
			lastIndex = index;

			if (current->left)
				q.push({ current->left,2 * index + 1 });

			if (current->right)
				q.push({ current->left,2 * index + 2 });

		}
	}

	bool isCompleteBT = (lastIndex == totalNodes - 1);

	bool isFullBT = (totalNodes == (1 << height) - 1);

	return { isCompleteBT,isFullBT };
}

/*
Lowest Common Ancestor
Given a binary tree and two nodes p and q in the tree, find their lowest common ancestor (LCA).

1. If the two nodes are not in the same subtree (e.g., one is on the leftmost subtree and the other is on the rightmost subtree), the recursive execution will eventually return two non-null values for left and right. At this point, the current root node is their lowest common ancestor (LCA).
2. If both nodes belong to the same subtree (either extreme left or right), when the first node (p or q) is found during the recursive search, there is no need to continue searching further. Since both nodes are guaranteed to be present in this binary tree, the first encountered node will be their LCA.

Time and Space Complexity: O(n) and O(h)
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	// If the current node is null, or we find either p or q, return the current node
	if (root == nullptr || root == p || root == q) {
		return root;
	}

	// Recursively search in the left and right subtree
	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);

	// If both left and right are non-null, the current node is the LCA
	if (left && right) {
		return root;
	}

	// If one side is non-null, return that side
	return left ? left : right;
}

/*
Inorder Successor in Binary Search Tree

1. If the node has a right subtree: Find the leftmost node in the right subtree. This can be found by continuously following the left child pointers of the nodes in the right subtree.
2. If the node does not have a right subtree: Use the parent pointer to traverse upwards until a node is found that is the left child of its parent. That parent node will be the successor of the target node.

Time and Space Complexity: O(n) and O(h)
*/
TreeNode* findLeftMost(TreeNode* node) {
	while (node->left)
		node = node->left;
	return node;
}

TreeNode* getSuccessor(TreeNode* node) {
	if (node == nullptr) return nullptr;

	if (node->right)
		return findLeftMost(node->right);

	TreeNode* current = node;
	TreeNode* parent = node->parent;
	while (parent && current == parent->right) {
		current = parent;
		parent = parent->parent;
	}
	return parent;
}

/*
Paper Folding Sequence
Given a paper that is folded n times in the same direction (downwards), unfold the paper and print the sequence of fold directions ("down" or "up") as they appear from left to right. The sequence should represent the folds seen on the paper after n folds.

This is a problem of sequential traversal in a binary tree.

Time and Space Complexity: O(n) and O(h)
*/
void printFolds(int level, int n, bool isDown) {
	if (level > n) return;

	printFolds(level + 1, n, true);

	cout << (isDown ? "down " : "up ");

	printFolds(level + 1, n, false);
}
