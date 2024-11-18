#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

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
