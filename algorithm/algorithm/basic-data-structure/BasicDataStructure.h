#ifndef BASIC_DATA_STRUCTURE_H
#define BASIC_DATA_STRUCTURE_H

#include <vector>
#include <algorithm>
#include <stack>
#include <memory>
#include <functional>
#include <optional>
#include <unordered_map>

using namespace std;

/*
Union-Find
The Union-Find, or Disjoint Set, is a data structure that efficiently handles merging and finding connected components within a set. It supports two main operations: union (to combine two sets) and find (to determine the representative, or root, of a set). With optimizations like path compression and union by size or rank, Union-Find achieves nearly constant time complexity for these operations.
Union-Find is commonly used to solve problems related to connectivity in graphs, such as finding connected components, determining if a graph is connected, and applications in Kruskal's algorithm for finding the minimum spanning tree. It is also used in network connectivity, clustering, and social network analysis.
*/

/*
Constructing Union-Find with Map
1. Define three maps for storage: one for the relationship between elements and their nodes, one for nodes and their root nodes, and one for the size of each set represented by each root node.
2. Initialize each element as its own node and root, setting the size of each set to 1.
3. To find the root of an element: repeatedly retrieve the parent of each node until reaching the root (a node that is its own parent). Use a stack to store nodes along the path and, upon finding the root, set each node along this path to directly point to the root.
4. To union two elements: find the roots of both elements. If they are different, union them by comparing the sizes of their sets. Link the root of the smaller set to the root of the larger set, updating the size accordingly.

With path compression and union by rank/size optimizations, Union-Find operations (initialization, union, find) have near-constant amortized time complexity O(¦Á(N)) and a space complexity of O(N).
*/
template <typename T>
class UnionFindNode {
public:
	T value;
	UnionFindNode(T v) : value(v) {}
};

template <typename T>
class UnionFindMap {
private:
	unordered_map<UnionFindNode<T>*, UnionFindNode<T>*> parent;
	unordered_map<T, UnionFindNode<T>*> nodes;
	unordered_map<UnionFindNode<T>*, int> sizeMap;

public:
	UnionFindMap(const vector<T>& values) {
		for (const T& v : values) {
			UnionFindNode<T>* node = new UnionFindNode<T>(v);
			nodes[v] = node;
			parent[node] = node;
			sizeMap[node] = 1;
		}
	}

	UnionFindNode<T>* findRoot(UnionFindNode<T>* cur) {
		stack<UnionFindNode<T>*> path;
		while (cur != parent[cur]) {
			path.push(cur);
			cur = parent[cur];
		}
		while (!path.empty()) {
			parent[path.top()] = cur;
			path.pop();
		}
		return cur;
	}

	bool isSameSet(const T& a, const T& b) {
		return findRoot(nodes[a]) == findRoot(nodes[b]);
	}

	void unionSets(const T& a, const T& b) {
		UnionFindNode<T>* aHead = findRoot(nodes[a]);
		UnionFindNode<T>* bHead = findRoot(nodes[b]);

		if (aHead != bHead) {
			int aSetSize = sizeMap[aHead];
			int bSetSize = sizeMap[bHead];
			UnionFindNode<T>* big = aSetSize >= bSetSize ? aHead : bHead;
			UnionFindNode<T>* small = (big == aHead) ? bHead : aHead;

			parent[small] = big;
			sizeMap[big] = aSetSize + bSetSize;
			sizeMap.erase(small);
		}
	}

	int setCount() const {
		return sizeMap.size();
	}
};

class UnionFindArray {
public:
	vector<int> parent, size, path;
	int numSets, rows, cols;
	bool isDynamicArray = false;
	// Constructor for a one-dimensional Union-Find
	UnionFindArray(int N) : parent(N), size(N, 1), path(N), numSets(N) {
		for (int i = 0; i < N; i++) {
			parent[i] = i;
		}
	}

	// Constructor for a two-dimensional grid-based Union-Find
	UnionFindArray(int m, int n) {
		numSets = 0;
		rows = m;
		cols = n;
		int totalsCells = rows * cols;
		parent.resize(totalsCells);
		size.resize(totalsCells);
		path.resize(totalsCells);
	}

	int getIndex(int r, int c) {
		return r * cols + c;
	}

	int connect(int r, int c) {
		int index = getIndex(r, c);
		if (size[index] == 0) {
			parent[index] = index;
			size[index] = 1;
			numSets++;

			unionSets(r - 1, c, r, c);
			unionSets(r + 1, c, r, c);
			unionSets(r, c - 1, r, c);
			unionSets(r, c + 1, r, c);
		}
		return numSets;
	}

	int findRoot(int i) {
		int helperIndex = 0;
		while (i != parent[i]) {
			path[helperIndex++] = i;
			i = parent[i];
		}

		for (helperIndex--; helperIndex >= 0; helperIndex--)
			parent[path[helperIndex]] = i;

		return i;
	}

	void setDynamicArray() {
		isDynamicArray = true;
	}

	void unionSets(int row1, int col1, int row2, int col2) {
		if (row1 < 0 || row1 == rows || row2 < 0 || row2 == rows
			|| col1 < 0 || col1 == cols || col2 < 0 || col2 == cols)
			return;

		int index1 = getIndex(row1, col1);
		int index2 = getIndex(row2, col2);

		if (isDynamicArray && (size[index1] == 0 || size[index2] == 0)) {
			return;
		}

		unionSets(index1, index2);
	}

	void unionSets(int index1, int index2) {
		int root1 = findRoot(index1);
		int root2 = findRoot(index2);
		if (root1 != root2) {
			if (size[root1] >= size[root2]) {
				size[root1] += size[root2];
				parent[root2] = root1;
			}
			else {
				size[root2] += size[root1];
				parent[root1] = root2;
			}
			numSets--;
		}
	}

	int getSetCount() const {
		return numSets;
	}
};

#endif // BASIC_DATA_STRUCTURE_H