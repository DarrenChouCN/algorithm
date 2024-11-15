#ifndef SKIPLISTMAP_H
#define SKIPLISTMAP_H

#include <vector>
#include <memory>
#include <optional>
#include <functional>

using namespace std;

/*
Skip List
A skip list is a data structure based on an ordered linked list, designed to accelerate search, insertion, and deletion operations through a multi-level index. It consists of multiple ¡°skip¡± pointers, where each level is a simplified version of the previous level. This allows the structure to "skip over" elements during traversal, significantly improving efficiency.
Skip lists perform consistently well under random insertions and deletions, with no need for explicit rebalancing operations. This makes them particularly suitable for data structures with frequent insertions and deletions in sorted order.

Characteristics:
1. Layered Structure: A skip list has multiple levels, from the lowest linked list up to the highest level, with fewer nodes at each higher level.
2. Randomization: Nodes are included in each level with a fixed probability (often 50%), giving the skip list a randomized structure.
3. Balance: The probabilistic insertion ensures that each level¡¯s node count approximates a logarithmic distribution, providing a balanced structure.
4. Flexibility: Skip lists support dynamic adjustment, allowing efficient insertion and deletion without complex rebalancing.

Complexity:
1. Search: Average time complexity is O(logn), with a worst case of O(n) (though this is very rare).
2. Insertion: Average time complexity is O(logn).
3. Deletion: Average time complexity is O(logn).

Advantages and Applications:
1. Advantages: Skip lists are simple to implement, support dynamic balancing, and in some cases, are easier to maintain compared to balanced trees.
2. Applications: Skip lists are commonly used in Redis, database indexing, and other scenarios that require fast lookups and ordered insertion.
*/
template <typename K, typename V, typename Comparator = less<K>>
class SkipListNode {
public:
    K key; // Node key
    V val; // Node value
    vector<shared_ptr<SkipListNode<K, V, Comparator>>> nextNodes;
    Comparator comp;

    SkipListNode(const K& k, const V& v, Comparator c = Comparator())
        : key(k), val(v), nextNodes(), comp(c) {
    }

    bool isKeyLess(const K& otherKey) const {
        return comp(key, otherKey);
    }

    bool isKeyEqual(const K& otherKey) const {
        return !comp(key, otherKey) && !comp(otherKey, key);
    }
};

template <typename K, typename V, typename Comparator = less<K>>
class SkipListMap {
public:
    int size;        // Current number of elements in the skip list
    int maxLevel;    // Maximum level of the skip list
    Comparator comp; // Comparator for key comparison
    shared_ptr<SkipListNode<K, V, Comparator>> head; // Head node of the skip list

    static constexpr double PROBABILITY = 0.5; // Probability factor for determining levels

    SkipListMap(Comparator c = Comparator())
        : size(0), maxLevel(0), comp(c), head(make_shared<SkipListNode<K, V, Comparator>>(K{}, V{}, c)) {
        head->nextNodes.push_back(nullptr);
    }

    void put(const K& key, const V& value) {
        auto less = mostRightLessNodeInTree(key);
        auto find = less->nextNodes[0];

        if (find && find->isKeyEqual(key)) {
            find->val = value;
        }
        else {
            size++;

            // Randomly determine the level for the new node
            int newNodeLevel = 0;
            while (static_cast<double>(rand()) / RAND_MAX < PROBABILITY) {
                newNodeLevel++;
            }

            // Expand the list if the new node level exceeds current maxLevel
            while (newNodeLevel > maxLevel) {
                head->nextNodes.push_back(nullptr);
                maxLevel++;
            }

            // Create a new node with the given key and value
            auto newNode = make_shared<SkipListNode<K, V, Comparator>>(key, value, comp);
            newNode->nextNodes.resize(newNodeLevel + 1, nullptr);

            // Insert the new node at each level up to newNodeLevel
            auto pre = head;
            for (int level = maxLevel; level >= 0; --level) {
                // Find the rightmost node with key < given key at the current level
                pre = mostRightLessNodeInLevel(key, pre, level);

                // Adjust pointers if the current level is within newNodeLevel
                if (level <= newNodeLevel) {
                    newNode->nextNodes[level] = pre->nextNodes[level];
                    pre->nextNodes[level] = newNode;
                }
            }
        }
    }

    // Check if a key exists in the skip list
    bool containsKey(const K& key) const {
        auto less = mostRightLessNodeInTree(key);
        auto next = less->nextNodes[0];
        return next && next->isKeyEqual(key);
    }

    // Retrieve the value associated with the given key
    optional<V> get(const K& key) const {
        auto less = mostRightLessNodeInTree(key);
        auto next = less->nextNodes[0];
        return (next && next->isKeyEqual(key)) ? optional<V>{next->val} : nullopt;
    }

    // Remove the node with the specified key from the skip list
    void remove(const K& key) {
        if (!containsKey(key)) return;

        size--;
        auto pre = head;
        for (int level = maxLevel; level >= 0; --level) {
            // Find the rightmost node in this level where node->key < key
            pre = mostRightLessNodeInLevel(key, pre, level);
            auto next = pre->nextNodes[level];

            // If `next` is the node with the target key, adjust pointers to remove it
            if (next && next->isKeyEqual(key)) {
                pre->nextNodes[level] = next->nextNodes[level];
            }

            // Reduce max level if the current level only has the head node
            if (level != 0 && pre == head && !pre->nextNodes[level]) {
                head->nextNodes.pop_back();
                maxLevel--;
            }
        }
    }

    // Returns the first key in the skip list, if it exists
    optional<K> firstKey() const {
        return head->nextNodes[0] ? optional<K>{head->nextNodes[0]->key} : nullopt;
    }

    // Returns the last key in the skip list, if it exists
    optional<K> lastKey() const {
        auto cur = head;
        for (int level = maxLevel; level >= 0; --level) {
            auto next = cur->nextNodes[level];
            while (next) {
                cur = next;
                next = cur->nextNodes[level];
            }
        }
        return cur != head ? optional<K>{cur->key} : nullopt;
    }

    // Returns the smallest key greater than or equal to the given key (ceiling key)
    optional<K> ceilingKey(const K& key) const {
        auto less = mostRightLessNodeInTree(key);
        auto next = less->nextNodes[0];
        return next ? optional<K>{next->key} : nullopt;
    }

    // Returns the largest key less than or equal to the given key (floor key)
    optional<K> floorKey(const K& key) const {
        auto less = mostRightLessNodeInTree(key);
        auto next = less->nextNodes[0];
        return (next && next->isKeyEqual(key)) ? optional<K>{next->key} : optional<K>{ less->key };
    }

private:
    // Traverse the skip list from the highest level downwards to find the rightmost node < key
    shared_ptr<SkipListNode<K, V, Comparator>> mostRightLessNodeInTree(const K& key) const {
        auto cur = head;
        for (int level = maxLevel; level >= 0; --level) {
            cur = mostRightLessNodeInLevel(key, cur, level);
        }
        return cur;
    }

    // Find the rightmost node at a specific level where node->key < key
    shared_ptr<SkipListNode<K, V, Comparator>> mostRightLessNodeInLevel(const K& key, shared_ptr<SkipListNode<K, V, Comparator>> cur, int level) const {
        auto next = cur->nextNodes[level];
        while (next && next->isKeyLess(key)) {
            cur = next;
            next = cur->nextNodes[level];
        }
        return cur;
    }
};

#endif // !SKIPLISTMAP_H
