#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "../common.h"

using namespace std;

/*
To solve graph-related algorithm problems, regardless of the initial data structure provided (such as an adjacency matrix, adjacency list, or even an array), it is recommended to first convert the given data structure into a more commonly used graph structure. This structure should primarily consist of nodes and edges:
a. Graph Structure: Includes both node and edge structures.
b. Edge Structure: Contains weight, source, and destination.
c. Node Structure: Includes the node's value, in-degree, out-degree, a set of adjacent nodes it connects to, and a collection of edges originating from it.
*/

/*
Breadth First Search

Time and Space Complexity: O(V+E) and O(V)
*/
void BFS(Graph& graph, int startIndex) {
	if (startIndex >= graph.nodes.size()) return;

	queue<Node*> nodeQueue;
	unordered_set<Node*> visited;

	Node* startNode = graph.nodes[startIndex];
	nodeQueue.push(startNode);
	visited.insert(startNode);

	while (!nodeQueue.empty()) {
		Node* currentNode = nodeQueue.front();
		nodeQueue.pop();

		cout << currentNode->value << " ";

		for (Node* adjacentNode : currentNode->adjacentNodes) {
			if (visited.find(adjacentNode) == visited.end()) {
				nodeQueue.push(adjacentNode);
				visited.insert(adjacentNode);
			}
		}
	}
}

/*
Depth First Search

Time and Space Complexity: O(V+E) and O(V)
*/
void DFS(Graph& graph, int startIndex) {
	if (startIndex >= graph.nodes.size()) return;

	stack<Node*> nodeStack;
	unordered_set<Node*> visited;

	Node* startNode = graph.nodes[startIndex];
	nodeStack.push(startNode);
	visited.insert(startNode);

	while (!nodeStack.empty()) {
		Node* currentNode = nodeStack.top();
		nodeStack.pop();

		cout << currentNode->value << " ";

		vector<Node*> adjacentNodes = currentNode->adjacentNodes;
		for (auto it = adjacentNodes.rbegin(); it != adjacentNodes.rend(); ++it) {
			Node* adjacentNode = *it;
			if (visited.find(adjacentNode) == visited.end()) {
				nodeStack.push(adjacentNode);
				visited.insert(adjacentNode);
			}
		}
	}
}

/*
Topological Sort (Kahn algorithm)

Time and Space Complexity: O(V+E) and O(V)
*/
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

/*
 Minimum Spanning Tree (Kruskal Algorithm)
 Kruskal's algorithm is designed to find the MST of a given undirected, weighted graph. The algorithm starts by sorting all edges in the graph by their weights in ascending order and then iteratively adds edges to the MST as long as they do not form a cycle. The algorithm uses a structure to track the connectivity of nodes to prevent cycles, which can be managed using an unordered_map.

1. Sort all edges of the graph in ascending order by weight. Use an unordered_map to track the parent (or root) of each node, initializing each node to be its own parent.
2. Iterate through the sorted edges, and for each edge:
	a. Use the findSet function to determine the root of each node connected by the edge.
	b. If the roots are different, the nodes belong to separate components:
		1) Add the edge to the Minimum Spanning Tree (MST).
		2) Merge the components by updating the unordered_map.
3. If the roots of the two nodes are the same, skip the edge to avoid forming a cycle. Continue until the MST contains exactly V−1 edges, where V is the number of nodes in the graph.

Time and Space Complexity: O(ElogE) and O(E+V)
*/
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


/*
Minimum Spanning Tree (Prim Algorithm)
Prim's algorithm is another method for finding the MST of a graph. Unlike Kruskal's algorithm, which starts with the edges and builds the MST by adding the smallest edges, Prim's algorithm starts with a single vertex and grows the MST one edge at a time by selecting the smallest edge that connects a new vertex to the tree.

1. Choose any node as the starting point and retrieve all the edges associated with this node. Insert these edges into a priority queue (min-heap).
2. Traverse the priority queue. Since it is a min-heap, the edge with the smallest weight will always be extracted first.
3. For the extracted edge, get its endpoint (target node). If the target node has not been visited, add this node and its corresponding edge to the MST and mark the node as visited.
4. Insert all the edges adjacent to the newly added node into the priority queue (only if their endpoints have not been visited).
5. Repeat Steps 2-4 until the MST contains all nodes.

Time and Space Complexity: O((V+E)logV) and O(V+E)
*/
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

/*
Shortest Path (Dijkstra's Algorithm)
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
*/
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