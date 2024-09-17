#ifndef COMMON_H
#define COMMON_H

struct ListNode
{
	int val;
	ListNode* next;
	ListNode* random;
	ListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr),parent(nullptr) {}
};

#endif // COMMON_H
