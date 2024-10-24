#include <iostream>
#include "../common.h"

using namespace std;

/*
Morris Traversal Algorithm
The Morris traversal algorithm takes advantage of the abundant unused pointers in a binary tree (i.e., nodes whose left or right child is null) by creating a threaded binary tree to replace the space consumption of recursion or stacks.

1. Start with the cur pointer set to the root of the binary tree.

2. If the left child of cur is not null, proceed to find the rightmost node in the left subtree (denoted as mostRight):
	a. Rightmost Node Determination: If the right child of mostRight is null, set its right child to point to cur. Move cur to its left child (cur = cur.left).
	b. Return Path Configuration: If the right child of mostRight already points to cur, it implies the left subtree has been fully traversed. Restore the tree structure by setting the right child of mostRight to null. Move cur to its right child (cur = cur.right).

3. If the left child of cur is null, move cur directly to its right child (cur = cur.right).

4. Repeat the above steps until cur is null, which indicates that the traversal of the entire tree is complete.

Time and Space Complexity: O(n) and O(1)
*/

/*
Preorder and Inorder Traversals

Check if the current node has a left subtree

If the current node does not have a left subtree (cur->left is nullptr):
	Preorder Traversal: Visit the current node because there is no left subtree to traverse first.
	Inorder Traversal: Visit the current node according to the inorder rule.

If the current node has a left subtree, ind the rightmost node (denoted as mostRight) in the left subtree:
1. Creating a thread: If mostRight->right is nullptr (indicating no thread has been created):
	Preorder Traversal: Visit the current node before creating the thread.
	Set mostRight->right to point to the current node, creating the thread, and move to the left child (cur = cur->left).

2. Breaking the thread: If mostRight->right already points to the current node (indicating the left subtree has been traversed):
	Inorder Traversal: Visit the current node before breaking the thread.
	Set mostRight->right to nullptr, restoring the original tree structure, and move to the right child (cur = cur->right).

3. Postorder Traversal Timing: Postorder traversal is processed when the temporary thread between the rightmost node and the current node is removed, and after the entire traversal is completed. Nodes should be reversed and output without using extra space, by reversing the linked list and restoring it afterward.
*/

TreeNode* reverseEdge(TreeNode* from) {
	TreeNode* prev = nullptr;
	TreeNode* next = nullptr;
	TreeNode* cur = from;

	while (cur) {
		next = cur->right;
		cur->right = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

void collectReverse(TreeNode* from, TreeNode* to, vector<int>& postorder) {
	TreeNode* revHead = reverseEdge(from);
	TreeNode* cur = revHead;

	while (cur != nullptr) {
		postorder.push_back(cur->val);
		cur = cur->right;
	}

	// Reverse back to restore the original structure
	reverseEdge(revHead);
}

void printArr(string type, const vector<int>& arr) {
	cout << type << ": ";
	for (int num : arr)
		cout << num << " ";
	cout << endl;
}

void morrisTraversal(TreeNode* root) {
	/*
	While Morris traversal has an O(1) space complexity, the use of three arrays here is to help understand the timing of node visits in preorder, inorder, and postorder traversals. The arrays store results for clarity and demonstration purposes. In practical scenarios, Morris traversal doesn¡¯t require arrays, and the results can be output directly without additional storage.
	*/
	vector<int> preorder, inorder, postorder;

	TreeNode* cur = root;
	TreeNode* mostRight = nullptr;

	while (cur) {
		if (cur->left) {
			mostRight = cur->left;
			while (mostRight->right && mostRight->right != cur) {
				mostRight = mostRight->right;
			}

			// mostRight->right == nullptr
			if (!mostRight->right) {
				mostRight->right = cur;

				// preorder add
				preorder.push_back(cur->val);

				cur = cur->left;
				continue;
			}
			else {
				mostRight->right = nullptr;

				// postorder add
				collectReverse(cur->left, mostRight, postorder);
			}
		}
		else {
			// no left child, preorder add
			preorder.push_back(cur->val);
		}

		// inorder add
		inorder.push_back(cur->val);
		cur = cur->right;
	}

	if (root != nullptr)
		collectReverse(root, nullptr, postorder);

	// Output the traversal results
	printArr("Preorder", preorder);
	printArr("Inorder", inorder);
	printArr("Postorder", postorder);
}

/*
Is Binary Tree using Morris Algorithm
To determine if a binary tree is a Binary Search Tree (BST) using Morris traversal, only one additional pointer, 'pre', is needed to keep track of the previous node in the inorder sequence. The tree is a valid BST if, at every step, the current node¡¯s value is greater than 'pre''s value. It's important to note that Morris traversal temporarily modifies the tree¡¯s structure by changing the pointers, so the entire tree must be traversed before returning the final result to ensure that the structure is restored correctly.

Time and Space Complexity: O(n) and O(1)
*/
bool isBST(TreeNode* head) {
	if (!head) return true;


	TreeNode* cur = head;
	TreeNode* mostRight = nullptr;
	TreeNode* pre = nullptr;
	bool isValid = true;

	while (cur) {
		mostRight = cur->left;
		if (mostRight) {
			while (mostRight->right && mostRight->right != cur) {
				mostRight = mostRight->right;
			}

			if (!mostRight->right) {
				mostRight->right = cur;
				cur = cur->left;
				continue;
			}
			else {
				mostRight->right = nullptr;
			}
		}

		// Inorder visit: check if current node is in correct order compared to previous node
		if (pre != nullptr && pre->val >= cur->val) {
			isValid = false;
		}
		pre = cur;
		cur = cur->right;
	}

	return isValid;
}

/*
Tree's Min Height
1. The entire tree is traversed using the Morris traversal method, which avoids using extra recursion or stack space.
2. Used to track the depth of the current node during traversal. This value increases or decreases based on the structure of the left and right subtrees.
3. Whenever the traversal reaches the left subtree, it locates the rightmost node and creates a thread. Upon revisiting this node, the thread is removed and the minimum height is updated.
4. After completing the left subtree traversal, the right boundary is processed to ensure the height calculation of the entire tree is accurate.

Time and Space Complexity: O(n) and O(1)
*/
int minHeight(TreeNode* head) {
	if (!head) return 0;

	TreeNode* cur = head;
	TreeNode* mostRight = nullptr;
	int curLevel = 0;
	int minHeight = INT_MAX;

	while (cur) {
		mostRight = cur->left;
		if (mostRight) {
			int rightBoardSize = 1;
			while (mostRight->right && mostRight->right != cur) {
				rightBoardSize++;
				mostRight = mostRight->right;
			}
			if (!mostRight->right) {
				curLevel++;
				mostRight->right = cur;
				cur = cur->left;
				continue;
			}
			else {
				if (!mostRight->left) {
					minHeight = min(minHeight, curLevel);
				}
				curLevel -= rightBoardSize;
				mostRight->right = nullptr;
			}
		}
		else {
			curLevel++;
		}
		cur = cur->right;
	}

	// Process the right boundary of the tree
	cur = head;
	int finalRight = 1;
	while (cur->right) {
		finalRight++;
		cur = cur->right;
	}

	if (!cur->left && !cur->right) {
		minHeight = min(minHeight, finalRight);
	}

	return minHeight;
}

int mainMorrisTraversal() {
	// Build a simple binary tree
	TreeNode* root = new TreeNode(10);
	root->left = new TreeNode(5);
	root->right = new TreeNode(20);
	root->left->left = new TreeNode(1);
	root->left->right = new TreeNode(7);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(2);

	// Perform Morris traversal and print results
	morrisTraversal(root);

	return 0;
}
