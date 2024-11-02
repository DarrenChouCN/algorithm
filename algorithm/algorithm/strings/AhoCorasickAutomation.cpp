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
    string end;
    bool endUse;
    Node* fail;
    Node* nexts[26];

    Node() : end(""), endUse(false), fail(nullptr) {
        for (int i = 0; i < 26; i++) {
            nexts[i] = nullptr;
        }
    }
};

class ACAutomation {
private:
    Node* root;

public:
    ACAutomation() {
        root = new Node();
    }

    void insert(const string& s) {
        Node* cur = root;
        for (char ch : s) {
            int index = ch - 'a';
            if (cur->nexts[index] == nullptr) {
                cur->nexts[index] = new Node();
            }
            cur = cur->nexts[index];
        }
        cur->end = s;
    }

    void build() {
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            for (int i = 0; i < 26; ++i) {
                if (cur->nexts[i] != nullptr) {
                    Node* fail = cur->fail;
                    while (fail != nullptr && fail->nexts[i] == nullptr) {
                        fail = fail->fail;
                    }
                    cur->nexts[i]->fail = (fail != nullptr) ? fail->nexts[i] : root;
                    q.push(cur->nexts[i]);
                }
            }
        }
    }

    vector<string> containWords(const string& content) {
        vector<string> ans;
        Node* cur = root;

        for (char ch : content) {
            int index = ch - 'a';
            while (cur->nexts[index] == nullptr && cur != root) {
                cur = cur->fail;
            }
            cur = (cur->nexts[index] != nullptr) ? cur->nexts[index] : root;

            Node* follow = cur;
            while (follow != root) {
                if (follow->endUse) break;
                if (!follow->end.empty()) {
                    ans.push_back(follow->end);
                    follow->endUse = true;
                }
                follow = follow->fail;
            }
        }

        return ans;
    }

    ~ACAutomation() {
        deleteTrie(root);
    }

private:
    void deleteTrie(Node* node) {
        if (node == nullptr) return;
        for (Node* child : node->nexts) {
            deleteTrie(child);
        }
        delete node;
    }
};

int main() {
    ACAutomation ac;
    ac.insert("dhess");
    ac.insert("heaa");
    ac.insert("abcdheks");

    ac.build();

    vector<string> contains = ac.containWords("abcdhekskdjfafhasldkflskdjhwqaeruv");
    for (const string& word : contains) {
        cout << word << endl;
    }

    return 0;
}