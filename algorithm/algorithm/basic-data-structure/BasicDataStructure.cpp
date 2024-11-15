#include <iostream>
#include <string>
#include "SkipListMap.h"

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

int main() {
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
