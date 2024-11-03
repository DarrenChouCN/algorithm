#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
Aho-Corasick Automation (AC Automation Algorithm)
The Aho-Corasick Automaton is an enhancement of the Trie structure, adding a fail pointer to each node. For any given node, the fail pointer points to another node in the Trie that has the same element but with the longest possible matching suffix, and whose prefix matches as much of the current node's prefix as possible. By utilizing fail pointers, it efficiently finds potential matching positions within the fully constructed Trie, enabling quick transitions and avoiding redundant comparisons.

Constructing 'fail' Pointers (Time and Space Complexity: O(M) and O(M))
1. Initialization: Set the 'fail' pointer of the root node to null (or to the root itself, depending on the implementation). For each direct child of the root node, set its fail pointer to the root. This ensures that if there¡¯s a mismatch at a direct child of the root, it falls back to the root.

2. Breadth-First Search to Construct 'fail' Pointers:
	Perform a BFS traversal of the Trie.
	For each child node children[i] of the current node:
		i. Use the 'fail' pointer of the parent node to check if there is a node with the same character as children[i].
		ii. If a matching node is found: Set the 'fail' pointer of children[i] to this matching node.
		iii. If no matching node is found: Continue traversing up the 'fail' chain until a match is found or until reaching the root, in which case the 'fail' pointer is set to the root.
	At each step, merge the output list of the 'fail' node with the output list of children[i], so that children[i] inherits all possible matching patterns.

3. Enqueue Child Nodes: After processing each node, enqueue all its children to the BFS queue to continue the traversal until all 'fail' pointers are constructed.


Search Logic (Time and Space Complexity: O(N) and O(K))
1. Traverse each character of the text, matching it against the current node in the Trie. If the current node has a child corresponding to the character, update node to this child node and store the match (e.g., record the position or index of matching patterns from the output list).
2. If the current node does not have a child for the character, use the 'fail' pointer to jump to the 'fail' node and attempt to find a match for this character there. Follow the 'fail' chain upwards until either a matching node is found or the root is reached (reaching the root indicates a complete mismatch).
3. Perform the above steps for each character in the text, moving through the entire string. The combination of 'fail' pointer backtracking and the Trie structure ensures efficient matching without backtracking in the text.
4. Continue this process until the end of the text, recording all pattern matches found along the way.

Overall Time and Space Complexity: O(M + N) and O(M \times ¦² + K)
*/
class Node {
public:
	string word;
	bool isMatched;
	Node* fail;
	Node* children[26];

	Node() : word(""), isMatched(false), fail(nullptr) {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}
};

class AhoCorasick {
public:
	Node* root;

	AhoCorasick() {
		root = new Node();
	}

	void insert(const string& pattern) {
		Node* cur = root;
		for (char ch : pattern) {
			int index = ch - 'a';
			if (!cur->children[index]) {
				cur->children[index] = new Node();
			}
			cur = cur->children[index];
		}
		cur->word = pattern;
	}

	void buildFailureLinks() {
		queue<Node*> q;
		q.push(root);

		while (!q.empty()) {
			Node* cur = q.front();
			q.pop();

			for (int i = 0; i < 26; ++i) {
				if (cur->children[i]) {
					Node* fail = cur->fail;
					while (fail && !fail->children[i]) {
						fail = fail->fail;
					}
					cur->children[i]->fail = fail ? fail->children[i] : root;
					q.push(cur->children[i]);
				}
			}
		}
	}

	vector<string> search(const string& content) {
		vector<string> result;
		Node* cur = root;

		for (char ch : content) {
			int index = ch - 'a';
			while (!cur->children[index] && cur != root) {
				cur = cur->fail;
			}
			cur = cur->children[index] ? cur->children[index] : root;

			Node* follow = cur;
			while (follow != root) {
				if (follow->isMatched) break;
				if (!follow->word.empty()) {
					result.push_back(follow->word);
					follow->isMatched = true;
				}
				follow = follow->fail;
			}
		}

		return result;
	}

	void deleteTrie(Node* node) {
		if (!node) return;
		for (Node* child : node->children) {
			deleteTrie(child);
		}
		delete node;
	}

	~AhoCorasick() {
		deleteTrie(root);
	}
};

int mainAhoCorasick() {
	AhoCorasick ac;
	ac.insert("dhe");
	ac.insert("he");
	ac.insert("abcdheks");

	ac.buildFailureLinks();

	vector<string> contains = ac.search("abcdhekskdjfafhasldkflskdjhwqaeruv");
	for (const string& word : contains) {
		cout << word << endl;
	}

	return 0;
}
