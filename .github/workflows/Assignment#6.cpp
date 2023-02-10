#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node *l, Node *r) {
        return l->freq > r->freq;
    }
};

void printCodes(Node *root, string str, unordered_map<char, string> &huffmanCode) {
    if (!root) return;
    if (root->ch != '\0') {
        huffmanCode[root->ch] = str;
    }
    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

void huffmanCodes(string s, vector<int> f) {
    int n = s.size();
    vector<Node *> nodes;
    for (int i = 0; i < n; i++) {
        nodes.push_back(new Node(s[i], f[i]));
    }
    priority_queue<Node *, vector<Node *>, compare> q;
    for (Node *node : nodes) {
        q.push(node);
    }
    while (q.size() != 1) {
        Node *left = q.top();
        q.pop();
        Node *right = q.top();
        q.pop();
        int sum = left->freq + right->freq;
        Node *top = new Node('\0', sum, left, right);
        q.push(top);
    }
    Node *root = q.top();
    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    string s = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    huffmanCodes(s, f);
    return 0;
}
