#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
    int pass; 
    int end;  
    unordered_map<char, TrieNode*> next; 

    TrieNode() : pass(0), end(0) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        if (word.empty()) return;

        TrieNode* node = root;
        for (char ch : word) {
            if (node->next.find(ch) == node->next.end()) {
                node->next[ch] = new TrieNode();
            }
            node = node->next[ch];
            node->pass++;
        }
        node->end++;
    }

    void remove(const string& word) {
        if (!search(word)) return; 

        TrieNode* node = root;
        for (char ch : word) {
            if (--node->next[ch]->pass == 0) {
                deleteSubtree(node->next[ch]);
                node->next.erase(ch);
                return;
            }
            node = node->next[ch];
        }
        node->end--;
    }

    bool search(const string& word) {
        if (word.empty()) return false;
        TrieNode* node = root;
        for (char ch : word) {
            if (node->next.find(ch) == node->next.end()) {
                return false;
            }
            node = node->next[ch];
        }
        return node->end > 0;
    }

    int prefixCount(const string& prefix) {
        if (prefix.empty()) return 0;

        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->next.find(ch) == node->next.end()) {
                return 0;
            }
            node = node->next[ch];
        }
        return node->pass;
    }

private:
    void deleteSubtree(TrieNode* node) {
        for (auto& pair : node->next) {
            deleteSubtree(pair.second);
        }
        delete node;
    }
};