## Max Width of Binary Tree

This method for calculating the maximum width fundamentally utilizes the properties of a binary tree, specifically the formulas for calculating the indices of child nodes, and uses these indices to compute the width of the current level. It keeps track of the maximum width using a variable. Each time it traverses the tree, all nodes of the current level are added to the queue, and the size is predetermined. Thus, the number of nodes dequeued matches the number of nodes in the current level.

Time and Space Complexity: O(n) and O(n)
```cpp
int maxWidthOfBinaryTree(TreeNode* root) {
	if (root == nullptr) return 0;

	queue<pair<TreeNode*, int>> q;
	q.push({ root, 0 });
	int maxWidth = 0;

	while (!q.empty()) {
		int size = q.size();
		int left = q.front().second;
		int right = q.back().second;

		maxWidth = max(maxWidth, right - left + 1);

		for (int i = 0; i < size; ++i) {
			pair<TreeNode*, int> node = q.front();
			q.pop();
			int index = node.second;

			if (node.first->left) {
				q.push({ node.first->left, 2 * index });
			}
			if (node.first->right) {
				q.push({ node.first->right, 2 * index + 1 });
			}
		}
	}

	return maxWidth;
}
```

## Is Valid BST

In a BST, the left child is smaller than the parent node, so the maximum value allowed for the left subtree should be the parent node's value. Similarly, the right child is larger than the parent node, so the minimum value allowed for the right subtree should be the parent node's value. This is why, during the recursive validation, the maximum value for the left subtree is updated to the parent node's value, and the minimum value for the right subtree is updated to the parent node's value.

Time and Space Complexity: O(n) and O(h)

```cpp
bool isValidBST1(TreeNode* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
	if (root == nullptr) return true;

	if (root->val <= minVal || root->val >= maxVal)
		return false;

	return isValidBST1(root->left, minVal, root->val) && isValidBST1(root->right, root->val, maxVal);
}
```



In a BST, the left child is smaller than the parent node, and the parent node is smaller than the right child. During an in-order traversal, the sequence is left -> root -> right, meaning that the nodes visited earlier should be smaller. Therefore, prevVal must be less than current->val. If at any point prevVal is greater than or equal to current->val, it indicates that the tree is not a BST.

Time and Space Complexity: O(n) and O(h)

```cpp
bool isValidBST2(TreeNode* root) {
	if (root == nullptr) return true;

	stack<TreeNode*> s;
	TreeNode* current = root;
	long long prevVal = LLONG_MIN;

	while (current != nullptr || !s.empty()) {
		while (current != nullptr) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();

		if (prevVal >= current->val) return false;

		prevVal = current->val;
		current = current->right;
	}

	return true;
}
```

## Is Complete and Full Binary Tree
This implementation uses a single traversal of the binary tree with an O(n) time complexity to check if the tree is a complete binary tree, a full binary tree, and to calculate the tree's height, while also tracking the index of each node.

1. BFS: A queue is used to perform a level-order traversal (BFS), visiting each node exactly once, maintaining an O(n) complexity.
2. Multi-Tasking:

	a. During traversal, the index of each node is calculated. By comparing the last node's index with totalNodes - 1, it is possible to determine if the tree is a complete binary tree.

	b. The tree's height is calculated in the BFS by counting the levels. Using this height, the total nodes are compared with 2^h−1 to verify if the tree is a full binary tree.

	c. The height is incremented each time a new level is processed.

	d. The properties of a binary tree are used to track indices, assisting in verifying completeness.

This approach combines multiple checks (completeness, fullness, and height) into a single traversal, reducing redundant computations.

Time and Space Complexity: O(n) and O(n)

```cpp
pair<bool, bool> isCompleteAndFullBT(TreeNode* root) {
	if (root == nullptr) return { true,true };

	queue<pair<TreeNode*, int>> q;
	q.push({ root,0 });

	int totalNodes = 0, height = 0, lastIndex = 0;

	while (!q.empty()) {
		int levelSize = q.size();
		height++;

		for (int i = 0; i < levelSize; i++)
		{
			TreeNode* current = q.front().first;
			int index = q.front().second;

			q.pop();

			totalNodes++;
			lastIndex = index;

			if (current->left)
				q.push({ current->left,2 * index + 1 });

			if (current->right)
				q.push({ current->left,2 * index + 2 });

		}
	}

	bool isCompleteBT = (lastIndex == totalNodes - 1);

	bool isFullBT = (totalNodes == (1 << height) - 1);

	return { isCompleteBT,isFullBT };
}
```


## Lowest Common Ancestor
Given a binary tree and two nodes p and q in the tree, find their lowest common ancestor (LCA).

1. If the two nodes are not in the same subtree (e.g., one is on the leftmost subtree and the other is on the rightmost subtree), the recursive execution will eventually return two non-null values for left and right. At this point, the current root node is their lowest common ancestor (LCA).
2. If both nodes belong to the same subtree (either extreme left or right), when the first node (p or q) is found during the recursive search, there is no need to continue searching further. Since both nodes are guaranteed to be present in this binary tree, the first encountered node will be their LCA.

Time and Space Complexity: O(n) and O(h)

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	// If the current node is null, or we find either p or q, return the current node
	if (root == nullptr || root == p || root == q) {
		return root;
	}

	// Recursively search in the left and right subtree
	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);

	// If both left and right are non-null, the current node is the LCA
	if (left && right) {
		return root;
	}

	// If one side is non-null, return that side
	return left ? left : right;
}
```

## Inorder Successor in Binary Search Tree

1. If the node has a right subtree: Find the leftmost node in the right subtree. This can be found by continuously following the left child pointers of the nodes in the right subtree.
2. If the node does not have a right subtree: Use the parent pointer to traverse upwards until a node is found that is the left child of its parent. That parent node will be the successor of the target node.

Time and Space Complexity: O(n) and O(h)

```cpp
TreeNode* findLeftMost(TreeNode* node) {
	while (node->left)
		node = node->left;
	return node;
}

TreeNode* getSuccessor(TreeNode* node) {
	if (node == nullptr) return nullptr;

	if (node->right)
		return findLeftMost(node->right);

	TreeNode* current = node;
	TreeNode* parent = node->parent;
	while (parent && current == parent->right) {
		current = parent;
		parent = parent->parent;
	}
	return parent;
}
```

## Paper Folding Sequence
Given a paper that is folded n times in the same direction (downwards), unfold the paper and print the sequence of fold directions ("down" or "up") as they appear from left to right. The sequence should represent the folds seen on the paper after n folds.

This is a problem of sequential traversal in a binary tree.

Time and Space Complexity: O(n) and O(h)

```cpp
void printFolds(int level, int n, bool isDown) {
	if (level > n) return;

	printFolds(level + 1, n, true);

	cout << (isDown ? "down " : "up ");

	printFolds(level + 1, n, false);
}
```


## Topological Sort (Kahn algorithm)

Time and Space Complexity: O(V+E) and O(V)

```cpp
vector<int> topologicalSort(Graph& graph) {
	vector<int> result;

	queue<Node*> zeroInDegreeQueue;
	unordered_map<Node*, int> inDegreeMap;

	for (Node* node : graph.nodes) {
		inDegreeMap[node] = node->inDegree;
		if (node->inDegree == 0)
			zeroInDegreeQueue.push(node);
	}

	while (!zeroInDegreeQueue.empty()) {
		Node* currentNode = zeroInDegreeQueue.front();
		zeroInDegreeQueue.pop();
		result.push_back(currentNode->value);

		for (Node* adjacentNode : currentNode->adjacentNodes) {
			inDegreeMap[adjacentNode]--;
			if (inDegreeMap[adjacentNode] == 0)
				zeroInDegreeQueue.push(adjacentNode);
		}
	}

	if (result.size() != graph.nodes.size()) {
		cout << "The graph has a cycle, topological sort is not possible." << endl;
		return {};
	}

	return result;
}
```

## Minimum Spanning Tree (Kruskal Algorithm)
 Kruskal's algorithm is designed to find the MST of a given undirected, weighted graph. The algorithm starts by sorting all edges in the graph by their weights in ascending order and then iteratively adds edges to the MST as long as they do not form a cycle. The algorithm uses a structure to track the connectivity of nodes to prevent cycles, which can be managed using an unordered_map.

1. Sort all edges of the graph in ascending order by weight. Use an unordered_map to track the parent (or root) of each node, initializing each node to be its own parent.
2. Iterate through the sorted edges, and for each edge:

	a. Use the findSet function to determine the root of each node connected by the edge.

	b. If the roots are different, the nodes belong to separate components: Add the edge to the Minimum Spanning Tree (MST). Merge the components by updating the unordered_map.

3. If the roots of the two nodes are the same, skip the edge to avoid forming a cycle. Continue until the MST contains exactly V−1 edges, where V is the number of nodes in the graph.

Time and Space Complexity: O(ElogE) and O(E+V)

```cpp
bool compareEdges(Edge* a, Edge* b) {
	return a->weight < b->weight;
}

// Finds the root of a node's component to check connectivity and ensures no cycles are formed by checking if nodes are in the same component.
Node* findSet(Node* node, unordered_map<Node*, Node*>& parentMap) {
	while (node != parentMap[node]) {
		node = parentMap[node];
	}
	return node;
}

void unionSet(Node* node1, Node* node2, unordered_map<Node*, Node*>& parentMap) {
	Node* set1 = findSet(node1, parentMap);
	Node* set2 = findSet(node2, parentMap);
	if (set1 != set2) {
		parentMap[set2] = set1;
	}
}

vector<Edge*> kruskalMST(Graph& graph) {
	if (graph.edges.empty()) return {};

	vector<Edge*> mstEdges;
	unordered_map<Node*, Node*> parentMap;

	for (Node* node : graph.nodes)
		parentMap[node] = node;

	sort(graph.edges.begin(), graph.edges.end(), compareEdges);

	for (Edge* edge : graph.edges)
	{
		Node* startNode = graph.nodes[edge->start];
		Node* endNode = graph.nodes[edge->end];

		if (findSet(startNode, parentMap) != findSet(endNode, parentMap)) {
			mstEdges.push_back(edge);
			unionSet(startNode, endNode, parentMap);
		}
	}

	return mstEdges;
}
```


## Minimum Spanning Tree (Prim Algorithm)
Prim's algorithm is another method for finding the MST of a graph. Unlike Kruskal's algorithm, which starts with the edges and builds the MST by adding the smallest edges, Prim's algorithm starts with a single vertex and grows the MST one edge at a time by selecting the smallest edge that connects a new vertex to the tree.

1. Choose any node as the starting point and retrieve all the edges associated with this node. Insert these edges into a priority queue (min-heap).
2. Traverse the priority queue. Since it is a min-heap, the edge with the smallest weight will always be extracted first.
3. For the extracted edge, get its endpoint (target node). If the target node has not been visited, add this node and its corresponding edge to the MST and mark the node as visited.
4. Insert all the edges adjacent to the newly added node into the priority queue (only if their endpoints have not been visited).
5. Repeat Steps 2-4 until the MST contains all nodes.

Time and Space Complexity: O((V+E)logV) and O(V+E)

```cpp
int primMST(Graph& graph) {
	if (graph.nodes.empty()) return 0;

	int totalWeight = 0;

	unordered_set<Node*> visited;
	Node* startNode = graph.nodes[0];
	visited.insert(startNode);

	// Priority queue (min-heap) for selecting the edge with the smallest weight
	priority_queue<Edge*, vector<Edge*>, CompareEdgeWeight> minHeap;
	for (Edge* edge : startNode->edges)
		minHeap.push(edge);

	while (!minHeap.empty()) {
		Edge* currentEdge = minHeap.top();
		minHeap.pop();

		Node* targetNode = graph.nodes[currentEdge->end];
		// Skip if the target node is already in the MST
		if (visited.find(targetNode) != visited.end()) {
			continue;
		}

		visited.insert(targetNode);
		totalWeight += currentEdge->weight;

		for (Edge* edge : targetNode->edges)
		{
			if (visited.find(graph.nodes[edge->end]) == visited.end()) {
				minHeap.push(edge);
			}
		}
	}
	return totalWeight;
}
```

## Shortest Path (Dijkstra's Algorithm)
Dijkstra's algorithm is a well-known method for finding the shortest path from a given starting node (source) to all other nodes in a graph with non-negative edge weights. The algorithm relies on a greedy approach to progressively explore the shortest path to each node.

1. Use a hash table to store the shortest known distance from the starting node to every other node. Initialize the distance to the starting node as 0 and all other nodes' distances as infinity (∞), representing that they are initially unreachable. Initialize a priority queue (min-heap) to select the node with the smallest tentative distance efficiently.
2. From the distance map, choose the node with the smallest distance that has not yet been finalized. This node is considered to have the shortest known path from the starting point. Mark this node as "visited" to indicate that its shortest path has been determined and will not change in future iterations.
3. For each neighboring node of the selected node:

	a. Calculate the new potential distance as the sum of the shortest path to the selected node and the edge weight to the neighboring node.

	b. If this new distance is smaller than the current recorded distance in the path table, update the distance map with this smaller value.

	c. Push the neighboring nodes with their updated distances into the priority queue (min-heap).

4. Continue selecting the node with the smallest distance from the priority queue, updating the distances of its neighbors, and marking nodes as visited. Repeat the process until all nodes have been visited or the priority queue is empty.
5. Once the algorithm completes, the distance map will contain the shortest paths from the starting node to all other nodes.

Time and Space Complexity: O((V+E)logV) and O(V+E)

```cpp
void dijkstra(Graph& graph, Node* startNode) {
	unordered_set<Node*> visited;
	unordered_map<Node*, int> distanceMap;

	for (Node* node : graph.nodes) {
		distanceMap[node] = numeric_limits<int>::max();
	}
	distanceMap[startNode] = 0;

	priority_queue<pair<Node*, int>, vector<pair<Node*, int>>, CompareDistance> minHeap;
	minHeap.push({ startNode,0 });

	while (!minHeap.empty()) {
		Node* currentNode = minHeap.top().first;
		int currentDistance = minHeap.top().second;
		minHeap.pop();

		if (visited.find(currentNode) != visited.end()) {
			continue;
		}
		visited.insert(currentNode);

		for (Edge* edge : currentNode->edges) {
			Node* neighbor = graph.nodes[edge->end];
			int newDistance = currentDistance + edge->weight;

			if (newDistance < distanceMap[neighbor]) {
				distanceMap[neighbor] = newDistance;
				minHeap.push({ neighbor ,newDistance });
			}
		}
	}
}
```

## Union-Find
The Union-Find, or Disjoint Set, is a data structure that efficiently handles merging and finding connected components within a set. It supports two main operations: union (to combine two sets) and find (to determine the representative, or root, of a set). With optimizations like path compression and union by size or rank, Union-Find achieves nearly constant time complexity for these operations.

Union-Find is commonly used to solve problems related to connectivity in graphs, such as finding connected components, determining if a graph is connected, and applications in Kruskal's algorithm for finding the minimum spanning tree. It is also used in network connectivity, clustering, and social network analysis.
*/


Constructing Union-Find with Map
1. Define three maps for storage: one for the relationship between elements and their nodes, one for nodes and their root nodes, and one for the size of each set represented by each root node.
2. Initialize each element as its own node and root, setting the size of each set to 1.
3. To find the root of an element: repeatedly retrieve the parent of each node until reaching the root (a node that is its own parent). Use a stack to store nodes along the path and, upon finding the root, set each node along this path to directly point to the root.
4. To union two elements: find the roots of both elements. If they are different, union them by comparing the sizes of their sets. Link the root of the smaller set to the root of the larger set, updating the size accordingly.

With path compression and union by rank/size optimizations, Union-Find operations (initialization, union, find) have near-constant amortized time complexity O(α(N)) and a space complexity of O(N).

```cpp
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
```

## Number of Provinces

https://leetcode.com/problems/friend-circles/

There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
Return the total number of provinces.

1. Matrix Symmetry: Since city connections form an undirected graph, the matrix isConnected is symmetric. Only half of the matrix needs to be traversed, reducing redundant checks.
2. Connected Components: Cities are viewed as connected components in an undirected graph, where each component represents a province. Union-Find efficiently merges directly or indirectly connected cities into the same component.
3. Union-Find Efficiency: With path compression and union by rank, Union-Find operations are nearly constant, keeping the algorithm efficient even for large inputs.

Time and Space Complexity: Traversing half of the matrix gives O(N^2) time complexity, while Union-Find’s space complexity is O(N).
*/
int findCircleNum(vector<vector<int>>& isConnected) {
	int N = isConnected.size();
	UnionFindArray unionFind(N);

	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (isConnected[i][j] == 1)
				unionFind.unionSets(i, j);

	return unionFind.getSetCount();
}



## Number of Islands

https://leetcode.com/problems/number-of-islands/

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.



Recursion: This approach is suitable for smaller grids, as the recursion depth may lead to stack overflow in cases with large input sizes.

Time and Space Complexity : O(M*N) and O(M*N)

```cpp
void infect(vector<vector<char>>& grid, int i, int j) {
	int rows = grid.size();
	int cols = grid[0].size();

	// Base Case
	if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != '1')
		return;

	grid[i][j] = '0';

	// Recursively infect adjacent cells
	infect(grid, i - 1, j);
	infect(grid, i + 1, j);
	infect(grid, i, j - 1);
	infect(grid, i, j + 1);
}

int numIslandsRecursion(vector<vector<char>>& grid) {
	int rows = grid.size();
	if (rows == 0) return 0;
	int cols = grid[0].size();

	int islands = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (grid[i][j] == '1') {
				islands++;
				infect(grid, i, j);
			}

	return islands;
}

int numIslands(vector<vector<char>>& grid) {
	int rows = grid.size();
	if (rows == 0) return 0;
	int cols = grid[0].size();

	UnionFindArray unionFind(rows, cols);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			if (grid[r][c] == '1') {
				int index = unionFind.getIndex(r, c);
				unionFind.parent[index] = index;
				unionFind.numSets++;
			}

	for (int j = 1; j < cols; j++) {
		if (grid[0][j - 1] == '1' && grid[0][j] == '1') {
			unionFind.unionSets(0, j - 1, 0, j);
		}
	}

	for (int i = 1; i < rows; i++) {
		if (grid[i - 1][0] == '1' && grid[i][0] == '1') {
			unionFind.unionSets(i - 1, 0, i, 0);
		}
	}

	for (int i = 1; i < rows; i++)
		for (int j = 1; j < cols; j++)
			if (grid[i][j] == '1') {
				if (grid[i - 1][j] == '1') {
					unionFind.unionSets(i - 1, j, i, j);
				}
				if (grid[i][j - 1] == '1') {
					unionFind.unionSets(i, j - 1, i, j);
				}
			}

	return unionFind.getSetCount();
}
```

## Number of Islands II
A 2D grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

The main difference between numIslands2 and numIslands1 lies in the dynamic nature of the problem. In numIslands1, the islands are counted in a static grid where all land cells are predefined. In contrast, numIslands2 involves a dynamic grid where water cells are incrementally turned into land, requiring island count updates after each operation.

In this connect implementation, a cell (r, c) is first converted to a 1D index. If the cell is water (indicated by size[index] == 0), it’s marked as land by setting its parent to itself, initializing its size to 1, and incrementing the island count (numSets++). Then, it attempts to merge with any adjacent land cells by calling unionSets on its four neighbors. Finally, it returns the updated number of islands (numSets).

Time and Space Complexity : O(k×α(N)) and O(M*N)

```cpp
vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
	UnionFindArray unionFind(m, n);
	unionFind.setDynamicArray();
	vector<int> result;
	for (const auto& position : positions) {
		int numSets = unionFind.connect(position[0], position[1]);
		result.push_back(numSets);
	}
	return result;
}
```



## AVL Tree
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

```cpp
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
```


## Size Balanced Tree
Difference between Size Balanced Tree and AVL Tree:
A Size Balanced (SB) Tree is a self-balancing binary search tree that maintains balance by ensuring size constraints across its subtrees, rather than strict height constraints like in an AVL tree. While AVL trees focus on keeping the tree height balanced to minimize path length, SB trees balance by comparing subtree sizes and performing rotations only when the size imbalance exceeds a certain threshold. This typically results in fewer rotations and slightly faster insertion/deletion operations in some cases, though SB trees may not achieve as strict height balance as AVL trees.

Time and Space Complexity of SB Tree:
The time complexity for search, insertion, and deletion operations in an SB Tree is O(logn) on average, similar to other balanced trees like AVL and Red-Black trees. However, due to its size-based balancing, it may experience slightly better performance in practice under certain workloads. The space complexity of an SB Tree is O(n), as it stores one node per element plus a small amount of additional storage for balancing metadata.

```cpp
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
```
