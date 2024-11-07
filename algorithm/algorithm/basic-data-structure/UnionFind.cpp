#include <unordered_map>
#include <stack>
#include <vector>

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
private:
	vector<int> parent;
	vector<int> size;
	vector<int> help;
	int sets;

public:
	UnionFindArray(int N) : parent(N), size(N, 1), help(N), sets(N) {
		for (int i = 0; i < N; i++) {
			parent[i] = i;
		}
	}

	int findRoot(int i) {
		int hi = 0;
		while (i != parent[i]) {
			help[hi++] = i;
			i = parent[i];
		}

		for (hi--; hi >= 0; hi--)
			parent[help[hi]] = i;

		return i;
	}

	void unionSets(int i, int j) {
		int f1 = findRoot(i);
		int f2 = findRoot(j);
		if (f1 != f2) {
			if (size[f1] >= size[f2]) {
				size[f1] += size[f2];
				parent[f2] = f1;
			}
			else {
				size[f2] += size[f1];
				parent[f1] = f2;
			}
			sets--;
		}
	}

	int getSetCount() const {
		return sets;
	}
};

/*
Number of Provinces (https://leetcode.com/problems/friend-circles/)
There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
Return the total number of provinces.

1. Matrix Symmetry: Since city connections form an undirected graph, the matrix isConnected is symmetric. Only half of the matrix needs to be traversed, reducing redundant checks.
2. Connected Components: Cities are viewed as connected components in an undirected graph, where each component represents a province. Union-Find efficiently merges directly or indirectly connected cities into the same component.
3. Union-Find Efficiency: With path compression and union by rank, Union-Find operations are nearly constant, keeping the algorithm efficient even for large inputs.

Time and Space Complexity: Traversing half of the matrix gives O(N^2) time complexity, while Union-Find¡¯s space complexity is O(N).
*/
class FindCircleNum {
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int N = isConnected.size();
		UnionFindArray unionFind(N);

		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if (isConnected[i][j] == 1)
					unionFind.unionSets(i, j);

		return unionFind.getSetCount();
	}
};


/*
Number of Islands
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
*/
