/*
Size Balanced Tree
Difference between Size Balanced Tree and AVL Tree:
A Size Balanced (SB) Tree is a self-balancing binary search tree that maintains balance by ensuring size constraints across its subtrees, rather than strict height constraints like in an AVL tree. While AVL trees focus on keeping the tree height balanced to minimize path length, SB trees balance by comparing subtree sizes and performing rotations only when the size imbalance exceeds a certain threshold. This typically results in fewer rotations and slightly faster insertion/deletion operations in some cases, though SB trees may not achieve as strict height balance as AVL trees.

Time and Space Complexity of SB Tree:
The time complexity for search, insertion, and deletion operations in an SB Tree is O(logn) on average, similar to other balanced trees like AVL and Red-Black trees. However, due to its size-based balancing, it may experience slightly better performance in practice under certain workloads. The space complexity of an SB Tree is O(n), as it stores one node per element plus a small amount of additional storage for balancing metadata.
*/
#ifndef SIZE_BALANCED_TREE_MAP_H
#define SIZE_BALANCED_TREE_MAP_H

#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;

template <typename K, typename V, typename Comparator = less<K>>
class SizeBalancedTreeMap {
private:
    struct SBTNode {
        K key;
        V value;
        unique_ptr<SBTNode> left;
        unique_ptr<SBTNode> right;
        int size;

        SBTNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), size(1) {}
    };

    unique_ptr<SBTNode> root;
    Comparator comp;

    int getNodeSize(const unique_ptr<SBTNode>& node) const {
        return node ? node->size : 0;
    }

    int getNodeSize(const SBTNode* node) const {
        return node ? node->size : 0;
    }

    // Right Rotate
    unique_ptr<SBTNode> rightRotate(unique_ptr<SBTNode> cur) {
        auto leftNode = move(cur->left);
        cur->left = move(leftNode->right);
        leftNode->right = move(cur);

        leftNode->size = getNodeSize(leftNode->left) + getNodeSize(leftNode->right) + 1;
        leftNode->right->size = 
            getNodeSize(leftNode->right->left) + getNodeSize(leftNode->right->right) + 1;
        return leftNode;
    }

    // Left Rotate
    unique_ptr<SBTNode> leftRotate(unique_ptr<SBTNode> cur) {
        auto rightNode = move(cur->right);
        cur->right = move(rightNode->left);
        rightNode->left = move(cur);

        rightNode->size = getNodeSize(rightNode->left) + getNodeSize(rightNode->right) + 1;
        rightNode->left->size =
            getNodeSize(rightNode->left->left) + getNodeSize(rightNode->left->right) + 1;
        return rightNode;
    }

    // Recursively Maintain
    unique_ptr<SBTNode> maintain(unique_ptr<SBTNode> cur) {
        if (!cur) return nullptr;

        int leftSize = getNodeSize(cur->left);
        int leftLeftSize = getNodeSize(cur->left ? cur->left->left.get() : nullptr);
        int leftRightSize = getNodeSize(cur->left ? cur->left->right.get() : nullptr);

        int rightSize = getNodeSize(cur->right);
        int rightLeftSize = getNodeSize(cur->right ? cur->right->left.get() : nullptr);
        int rightRightSize = getNodeSize(cur->right ? cur->right->right.get() : nullptr);

        // LL case
        if (leftLeftSize > rightSize) {
            cur = rightRotate(move(cur));
            cur->right = maintain(move(cur->right));
            cur = maintain(move(cur));
        }
        //LR case
        else if (leftRightSize > rightSize) {
            cur->left = leftRotate(move(cur->left));
            cur = rightRotate(move(cur));
            cur->left = maintain(move(cur->left));
            cur->right = maintain(move(cur->right));
            cur = maintain(move(cur));
        }
        //RR case
        else if (rightRightSize > leftSize) {
            cur = leftRotate(move(cur));
            cur->left = maintain(move(cur->left));
            cur = maintain(move(cur));
        }
        //RL case
        else if (rightLeftSize > leftSize) {
            cur->right = rightRotate(move(cur->right));
            cur = leftRotate(move(cur));
            cur->left = maintain(move(cur->left));
            cur->right = maintain(move(cur->right));
            cur = maintain(move(cur));
        }

        return cur;
    }

    unique_ptr<SBTNode> add(unique_ptr<SBTNode> cur, const K& key, const V& value) {
        if (!cur) return make_unique<SBTNode>(key, value);

        cur->size++;
        if (comp(key, cur->key))
            cur->left = add(move(cur->left), key, value);
        else
            cur->right = add(move(cur->right), key, value);

        return maintain(move(cur));
    }

    unique_ptr<SBTNode> remove(unique_ptr<SBTNode> cur, const K& key) {
        if (!cur) return nullptr;

        cur->size--;
        if (comp(key, cur->key)) {
            cur->left = remove(move(cur->left), key);
        }
        else if (comp(cur->key, key)) {
            cur->right = remove(move(cur->right), key);
        }
        else {
            if (!cur->left) return move(cur->right);
            if (!cur->right) return move(cur->left);

            auto successor = moveMin(move(cur->right));
            successor->right = move(cur->right);
            successor->left = move(cur->left);
            successor->size = getNodeSize(successor->left) + getNodeSize(successor->right) + 1;
            return maintain(move(successor));
        }

        return maintain(move(cur));
    }

    unique_ptr<SBTNode> moveMin(unique_ptr<SBTNode> cur) {
        if (!cur->left) return move(cur);
        cur->left = moveMin(move(cur->left));
        cur->size = getNodeSize(cur->left) + getNodeSize(cur->right) + 1;
        return maintain(move(cur));
    }

    SBTNode* findLastNoSmallIndex(const unique_ptr<SBTNode>& cur, const K& key) const {
        SBTNode* ans = nullptr;
        auto node = cur.get();

        while (node) {
            if (!comp(node->key, key) && !comp(key, node->key)) {
                ans = node;
                break;
            }
            else if (comp(key, node->key)) {
                node = node->left.get();
            }
            else {
                ans = node;
                node = node->right.get();
            }
        }

        return ans;
    }

public:
    SizeBalancedTreeMap(Comparator c = Comparator()) : root(nullptr), comp(c) {}

    int size() const {
        return getNodeSize(root);
    }

    bool containsKey(const K& key) const {
        auto lastNode = findLastNoSmallIndex(root, key);
        return lastNode && !comp(key, lastNode->key) && !comp(lastNode->key, key);
    }

    void put(const K& key, const V& value) {
        root = add(move(root), key, value);
    }

    void remove(const K& key) {
        if (containsKey(key))
            root = remove(move(root), key);
    }

    optional<V> get(const K& key) const {
        auto lastNode = findLastNoSmallIndex(root, key);
        return (lastNode && !comp(key, lastNode->key) && !comp(lastNode->key, key))
            ? optional<V>{lastNode->value} : nullopt;
    }
};

#endif // SIZE_BALANCED_TREE_MAP_H
