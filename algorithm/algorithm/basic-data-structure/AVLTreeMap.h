#ifndef AVLTREEMAP_H
#define AVLTREEMAP_H

#include <iostream>
#include <algorithm>

template <typename K, typename V>
class AVLNode {
public:
	K key;
	V value;
	AVLNode* left;  // left child
	AVLNode* right; // right child
	int height;     // height of the node

	AVLNode(K k, V v);
};


template<typename K, typename V>
class AVLTreeMap {
private:
	int size;
	AVLNode<K, V>* root;

	AVLNode<K, V>* rightRotate(AVLNode<K, V>* node);

	AVLNode<K, V>* leftRotate(AVLNode<K, V>* node);

	AVLNode<K, V>* maintain(AVLNode<K, V>* node);

	AVLNode<K, V>* findLastIndex(const K& key);

	AVLNode<K, V>* findLastNoSmallIndex(const K& key);

	AVLNode<K, V>* findLastNoBigIndex(const K& key);

	AVLNode<K, V>* add(AVLNode<K, V>* cur, K& key, V& value);

	AVLNode<K, V>* deleteNode(AVLNode<K, V>* cur, K& key);

public:
	AVLTreeMap();
	~AVLTreeMap();

	int getSize() const;

	bool containsKey(const K& key) const;

	void put(const K& key, const V& value);

	void remove(const K& key);

	V* get(const K& key) const;

	K* firstKey() const;

	K* lastKey() const;

	K* floorKey(const K& key) const;

	K* ceilingKey(const K& key) const;

};

#endif // !AVLTREEMAP_H

