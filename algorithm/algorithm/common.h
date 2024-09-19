#ifndef COMMON_H
#define COMMON_H

#include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode* random;
	ListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct Edge
{
	int weight;
	int start;
	int end;

	Edge(int w, int s, int e) : weight(w), start(s), end(e) {}
};

struct Node
{
	int value;
	int inDegree = 0;
	int outDegree = 0;
	vector<Node*> adjacentNodes;
	vector<Edge*> edges;

	Node(int v) :value(v) {}
};

struct Graph
{
	vector<Node*> nodes;
	vector<Edge*> edges;

	void addNode(int value) {
		nodes.push_back(new Node(value));
	}

	void addEdge(int startIndex, int endIndex, int weight) {
		Node* startNode = nodes[startIndex];
		Node* endNode = nodes[endIndex];
		Edge* newEdge = new Edge(weight, startIndex, endIndex);

		startNode->adjacentNodes.push_back(endNode);
		startNode->edges.push_back(newEdge);

		startNode->outDegree++;
		startNode->inDegree++;

		edges.push_back(newEdge);
	}

	~Graph() {
		for (auto node : nodes)
			delete node;

		for (auto edge : edges)
			delete edge;
	}
};

struct CompareEdgeWeight
{
	bool operator()(Edge* a, Edge* b) {
		return a->weight > b->weight;
	}
};

struct CompareDistance
{
	bool operator()(pair<Node*, int> a, pair<Node*, int> b) {
		return a.second > b.second;
	}
};


#endif // COMMON_H
