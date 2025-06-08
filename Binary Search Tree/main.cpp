#include <iostream>
#include <cmath>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        left = right = nullptr;
    }
};

class BSTree {
public:
    Node* root;

    BSTree() {
        root = nullptr;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        // No duplicates
        return node;
    }

    void insertValue(int key) {
        root = insert(root, key);
    }
    
    int height(Node* root) {
    if (!root) return -1;
    return 1 + max(height(root->left), height(root->right));
    }
};

int main() {
    BSTree tree;
    int n_values[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    for(int i = 0; i < 12; ++i) {
        for (int j = 0; j < n_values[i]; ++j) {
            tree.insertValue(rand()*10000);
        }
        cout << "n = " << n_values[i] << " , height = " << tree.height(tree.root) << " , height / log2() = " \
        << tree.height(tree.root) / log2(n_values[i]) << "\n";
    }
    
    
    return 0;
}

