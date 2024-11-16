/*
AVL Tree
An AVL tree maintains a balance factor (-1,0,1) for every node, ensuring the height difference between the left and right subtrees is at most 1. It follows the BST property where the left subtree contains smaller keys, and the right subtree contains larger keys. The tree performs single or double rotations (left or right) to maintain balance after insertion or deletion.

Common Use Cases:
1. Useful in scenarios requiring fast ordered insertions, deletions, and lookups, such as implementing maps or sets.
2. Often used in databases for maintaining sorted indexes.
3. Helps in managing ranges or time-based data efficiently.

Complexity:
Time Complexity: Search, Insert, Delete: O(logN) (height is logarithmic due to balancing).
Space Complexity: O(N) for storing nodes.

Construction:
Start with an empty tree. Insert nodes one by one following the BST rule. After each insertion, calculate the balance factor and perform necessary rotations to maintain balance.

Additional Notes:
1. Comparison with Red-Black Trees: AVL trees provide stricter balancing than Red-Black trees, leading to faster lookups but slower insertions and deletions.
2. Custom Comparators: Comparators can be used to define custom orderings, making it flexible for various data types.
*/
#ifndef AVL_TREE_MAP_H
#define AVL_TREE_MAP_H

#include <memory>
#include <optional>
#include <functional>
#include <algorithm>

using namespace std;

template <typename K, typename V, typename Comparator = less<K>>
class AVLTreeMap {
private:
    struct AVLNode {
        K key;
        V value;
        unique_ptr<AVLNode> left;
        unique_ptr<AVLNode> right;
        int height;

        AVLNode(K k, V v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    unique_ptr<AVLNode> root;
    int size;
    Comparator comp;

    int getHeight(const unique_ptr<AVLNode>& node) const {
        return node ? node->height : 0;
    }

    int getBalance(const unique_ptr<AVLNode>& node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    /*
        cur					 left
       /					/    \
     left		->      left.r   cur
       \
        left.r
    */
    unique_ptr<AVLNode> rightRotate(unique_ptr<AVLNode> cur) {
        auto leftChild = move(cur->left);
        cur->left = move(leftChild->right);
        leftChild->right = move(cur);

        updateHeight(leftChild->right);
        updateHeight(leftChild);
        return leftChild;
    }

    /*
        cur                 right
          \               /      \
         right    ->    cur      right.r
        /				   \
      right.l			   right.l
    */
    unique_ptr<AVLNode> leftRotate(unique_ptr<AVLNode> cur) {
        auto rightChild = move(cur->right);
        cur->right = move(rightChild->left);
        rightChild->left = move(cur);

        updateHeight(rightChild->left);
        updateHeight(rightChild);
        return rightChild;
    }

    void updateHeight(unique_ptr<AVLNode>& node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    /*
    1. Calculate the heights of the left and right children. If the height difference (leftHeight - rightHeight) exceeds 1, the node is unbalanced.
    2. Left-Heavy Cases:
        LL Case: If the left subtree’s left child height (leftLeftHeight) is greater than or equal to the right child height (leftRightHeight), perform a right rotation on cur.
        LR Case: If the left subtree’s right child is taller, perform a left rotation on cur->left, then a right rotation on cur.
    3. Right-Heavy Cases:
        RR Case: If the right subtree’s right child height (rightRightHeight) is greater than or equal to the left child height (rightLeftHeight), perform a left rotation on cur.
        RL Case: If the right subtree’s left child is taller, perform a right rotation on cur->right, then a left rotation on cur.
    4. Update cur’s height based on the maximum height of its left and right children after balancing.
    */
    unique_ptr<AVLNode> maintain(unique_ptr<AVLNode> node) {
        if (!node) return nullptr;

        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) < 0)
                // LR case: first perform a left rotation on cur->left, then a right rotation on cur
                node->left = leftRotate(move(node->left));
            // LL case: perform a right rotation on cur
            node = rightRotate(move(node));
        }
        else if (balance < -1) {
            if (getBalance(node->right) > 0)
                // RL case: first perform a right rotation on cur->right, then a left rotation on cur
                node->right = rightRotate(move(node->right));
            // RR case: perform a left rotation on cur
            node = leftRotate(move(node));
        }

        return node;
    }

    unique_ptr<AVLNode> add(unique_ptr<AVLNode> node, const K& key, const V& value) {
        if (!node) return make_unique<AVLNode>(key, value);

        if (comp(key, node->key))
            node->left = add(move(node->left), key, value);
        else if (comp(node->key, key))
            node->right = add(move(node->right), key, value);
        else
            node->value = value;

        return maintain(move(node));
    }

    unique_ptr<AVLNode> deleteNode(unique_ptr<AVLNode> node, const K& key) {
        if (!node) return nullptr;

        if (comp(key, node->key)) {
            node->left = deleteNode(move(node->left), key);
        }
        else if (comp(node->key, key)) {
            node->right = deleteNode(move(node->right), key);
        }
        else {
            if (!node->left) return move(node->right);
            if (!node->right) return move(node->left);

            auto successor = getMinNode(node->right);
            node->key = successor->key;
            node->value = successor->value;
            node->right = deleteMin(move(node->right));
        }

        return maintain(move(node));
    }

    AVLNode* getMinNode(const unique_ptr<AVLNode>& node) const {
        AVLNode* cur = node.get();
        while (cur && cur->left) cur = cur->left.get();
        return cur;
    }

    unique_ptr<AVLNode> deleteMin(unique_ptr<AVLNode> node) {
        if (!node->left) return move(node->right);
        node->left = deleteMin(move(node->left));
        return maintain(move(node));
    }

    AVLNode* findLastNoSmallIndex(const K& key) const {
        AVLNode* ans = nullptr;
        AVLNode* cur = root.get();
        while (cur) {
            if (!comp(cur->key, key) && !comp(key, cur->key)) {
                ans = cur;
                break;
            }
            else if (comp(key, cur->key)) {
                cur = cur->left.get();
            }
            else {
                ans = cur;
                cur = cur->right.get();
            }
        }
        return ans;
    }

    AVLNode* findLastNoBigIndex(const K& key) const {
        AVLNode* ans = nullptr;
        AVLNode* cur = root.get();
        while (cur) {
            if (!comp(cur->key, key) && !comp(key, cur->key)) {
                ans = cur;
                break;
            }
            else if (comp(key, cur->key)) {
                cur = cur->left.get();
            }
            else {
                ans = cur;
                cur = cur->right.get();
            }
        }
        return ans;
    }

public:
    AVLTreeMap(Comparator c = Comparator()) : root(nullptr), size(0), comp(c) {}

    int getSize() const {
        return size;
    }

    bool containsKey(const K& key) const {
        auto lastNode = findLastNoBigIndex(key);
        return lastNode && !comp(lastNode->key, key) && !comp(key, lastNode->key);
    }

    void put(const K& key, const V& value) {
        if (!containsKey(key)) size++;
        root = add(move(root), key, value);
    }

    void remove(const K& key) {
        if (containsKey(key)) {
            size--;
            root = deleteNode(move(root), key);
        }
    }

    optional<V> get(const K& key) const {
        auto lastNode = findLastNoBigIndex(key);
        return (lastNode && !comp(lastNode->key, key) && !comp(key, lastNode->key))
            ? optional<V>{lastNode->value} : nullopt;
    }

    optional<K> firstKey() const {
        auto cur = root.get();
        while (cur && cur->left) cur = cur->left.get();
        return cur ? optional<K>{cur->key} : nullopt;
    }

    optional<K> lastKey() const {
        auto cur = root.get();
        while (cur && cur->right) cur = cur->right.get();
        return cur ? optional<K>{cur->key} : nullopt;
    }

    optional<K> floorKey(const K& key) const {
        auto node = findLastNoBigIndex(key);
        return node ? optional<K>{node->key} : nullopt;
    }

    optional<K> ceilingKey(const K& key) const {
        auto node = findLastNoSmallIndex(key);
        return node ? optional<K>{node->key} : nullopt;
    }
};

#endif // AVL_TREE_MAP_H
