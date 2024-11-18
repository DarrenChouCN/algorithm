#include <iostream>
#include <string>
#include "SkipListMap.h"
#include "AVLTreeMap.h"
#include "SizeBalancedTreeMap.h"

using namespace std;

struct Apple {
    int size;
    Apple() : size(0) {}  
    Apple(int s) : size(s) {}
    bool operator<(const Apple& other) const { return size < other.size; }
};

struct AppleComparator {
    bool operator()(const Apple& a, const Apple& b) const {
        return a.size < b.size;
    }
};

// Skip List Test
void SkipListMapPrintAll(const SkipListMap<Apple, string, AppleComparator>& obj) {
    for (int i = obj.maxLevel; i >= 0; --i) {
        cout << "Level " << i << ": ";
        auto cur = obj.head;
        while (cur->nextNodes[i]) {
            auto next = cur->nextNodes[i];
            cout << "(" << next->key.size << ", " << next->val << ") ";
            cur = next;
        }
        cout << endl;
    }
    cout << endl;
}

int testSkipListMap() {
    SkipListMap<Apple, string, AppleComparator> test;

    // Insert a range of values into the skip list
    for (int i = 1; i <= 20; ++i) {
        test.put(Apple(i), "Apple " + to_string(i));
    }
    cout << "Initial skip list after inserting 20 elements:" << endl;
    SkipListMapPrintAll(test);

    // Test `containsKey`
    cout << "Contains Apple(5): " << test.containsKey(Apple(5)) << " // Expected: 1" << endl;
    cout << "Contains Apple(21): " << test.containsKey(Apple(21)) << " // Expected: 0" << endl;

    // Test `get`
    cout << "Value of Apple(5): " << *test.get(Apple(5)) << " // Expected: Apple 5" << endl;
    cout << "Value of Apple(21): " << (test.get(Apple(21)) ? *test.get(Apple(21)) : "null") << " // Expected: null" << endl;

    // Test `firstKey` and `lastKey`
    cout << "First key: " << test.firstKey()->size << " // Expected: 1" << endl;
    cout << "Last key: " << test.lastKey()->size << " // Expected: 20" << endl;

    // Test `ceilingKey` and `floorKey`
    cout << "Ceiling key for Apple(5): " << test.ceilingKey(Apple(5))->size << " // Expected: 5" << endl;
    cout << "Ceiling key for Apple(21): " << (test.ceilingKey(Apple(21)) ? to_string(test.ceilingKey(Apple(21))->size) : "null") << " // Expected: null" << endl;
    cout << "Floor key for Apple(5): " << test.floorKey(Apple(5))->size << " // Expected: 5" << endl;
    cout << "Floor key for Apple(0): " << (test.floorKey(Apple(0)) ? to_string(test.floorKey(Apple(0))->size) : "null") << " // Expected: null" << endl;

    // Remove some elements and check the structure
    cout << "\nRemoving elements Apple(1), Apple(10), and Apple(20)" << endl;
    test.remove(Apple(1));
    test.remove(Apple(10));
    test.remove(Apple(20));
    SkipListMapPrintAll(test);

    // Check first and last key after deletions
    cout << "First key after removals: " << test.firstKey()->size << " // Expected: 2" << endl;
    cout << "Last key after removals: " << test.lastKey()->size << " // Expected: 19" << endl;

    return 0;
}

void testAVLTreeMap() {
    AVLTreeMap<Apple, string, AppleComparator> tree;

    vector<pair<Apple, string>> apples = {
        {Apple(10), "Small Apple"},
        {Apple(20), "Medium Apple"},
        {Apple(30), "Large Apple"},
        {Apple(25), "Almost Large Apple"},
        {Apple(5), "Very Small Apple"},
        {Apple(15), "Between Small and Medium"},
        {Apple(35), "Extra Large Apple"}
    };

    for (const auto& [apple, description] : apples) {
        tree.put(apple, description);
    }

    cout << "Test get():" << endl;
    cout << "Apple(10): " << (tree.get(Apple(10)).has_value() ? *tree.get(Apple(10)) : "Not found") << endl;
    cout << "Apple(20): " << (tree.get(Apple(20)).has_value() ? *tree.get(Apple(20)) : "Not found") << endl;
    cout << "Apple(30): " << (tree.get(Apple(30)).has_value() ? *tree.get(Apple(30)) : "Not found") << endl;

    cout << "\nTest containsKey():" << endl;
    cout << "Contains Apple(25): " << (tree.containsKey(Apple(25)) ? "Yes" : "No") << endl;
    cout << "Contains Apple(100): " << (tree.containsKey(Apple(100)) ? "Yes" : "No") << endl;

    cout << "\nTest firstKey() and lastKey():" << endl;
    cout << "First Key: " << (tree.firstKey().has_value() ? to_string(tree.firstKey()->size) : "None") << endl;
    cout << "Last Key: " << (tree.lastKey().has_value() ? to_string(tree.lastKey()->size) : "None") << endl;

    cout << "\nTest floorKey() and ceilingKey():" << endl;
    cout << "Floor Key of 23: " << (tree.floorKey(Apple(23)).has_value() ? to_string(tree.floorKey(Apple(23))->size) : "None") << endl;
    cout << "Ceiling Key of 23: " << (tree.ceilingKey(Apple(23)).has_value() ? to_string(tree.ceilingKey(Apple(23))->size) : "None") << endl;
    cout << "Floor Key of 5: " << (tree.floorKey(Apple(5)).has_value() ? to_string(tree.floorKey(Apple(5))->size) : "None") << endl;
    cout << "Ceiling Key of 35: " << (tree.ceilingKey(Apple(35)).has_value() ? to_string(tree.ceilingKey(Apple(35))->size) : "None") << endl;

    cout << "\nTest remove():" << endl;
    tree.remove(Apple(20));
    cout << "After removing Apple(20), contains Apple(20): " << (tree.containsKey(Apple(20)) ? "Yes" : "No") << endl;
    cout << "After removing Apple(20), floorKey(23): " << (tree.floorKey(Apple(23)).has_value() ? to_string(tree.floorKey(Apple(23))->size) : "None") << endl;
}

void testSizeBalancedTreeMap() {
    SizeBalancedTreeMap<Apple, string, AppleComparator> sbt;

    vector<pair<Apple, string>> apples = {
        {Apple(10), "Small Apple"},
        {Apple(20), "Medium Apple"},
        {Apple(30), "Large Apple"},
        {Apple(25), "Almost Large Apple"},
        {Apple(5), "Very Small Apple"},
        {Apple(15), "Between Small and Medium"},
        {Apple(35), "Extra Large Apple"}
    };

    for (const auto& [apple, description] : apples) {
        sbt.put(apple, description);
    }

    cout << "Test get():" << endl;
    cout << "Apple(10): " << (sbt.get(Apple(10)).has_value() ? *sbt.get(Apple(10)) : "Not found") << endl;
    cout << "Apple(20): " << (sbt.get(Apple(20)).has_value() ? *sbt.get(Apple(20)) : "Not found") << endl;
    cout << "Apple(30): " << (sbt.get(Apple(30)).has_value() ? *sbt.get(Apple(30)) : "Not found") << endl;

    cout << "\nTest containsKey():" << endl;
    cout << "Contains Apple(25): " << (sbt.containsKey(Apple(25)) ? "Yes" : "No") << endl;
    cout << "Contains Apple(100): " << (sbt.containsKey(Apple(100)) ? "Yes" : "No") << endl;

    cout << "\nTest size():" << endl;
    cout << "Tree size: " << sbt.size() << endl;

    cout << "\nTest floorKey() and ceilingKey():" << endl;
    /*cout << "Floor Key of 23: " << (sbt.get(Apple(23)).has_value() ?
        to_string(sbt.get(Apple(23))->size) : "None") << endl;
    cout << "Ceiling Key of 23: " << (sbt.get(Apple(23)).has_value() ? 
        to_string(sbt.get(Apple(23))->size) : "None") << endl;*/

    cout << "\nTest remove():" << endl;
    sbt.remove(Apple(20));
    cout << "After removing Apple(20), contains Apple(20): " << (sbt.containsKey(Apple(20)) ? "Yes" : "No") << endl;
    cout << "After removing Apple(20), size: " << sbt.size() << endl;

    cout << "\nFinal tree contents:" << endl;
    for (const auto& [apple, description] : apples) {
        if (sbt.containsKey(apple)) {
            cout << "Apple(" << apple.size << "): " << *sbt.get(apple) << endl;
        }
    }
}


int main1() {
    testSizeBalancedTreeMap();
    return 0;
}