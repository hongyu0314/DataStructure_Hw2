#include <iostream>
#include <cmath>  //引入標頭檔
using namespace std;

class Node { // BST 用的結構 樹的基本單元
public:
    int key;
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        left = right = nullptr;
    }
};

class BSTree { // BST 的類別與程式區分方便復用 

public: // root 和宣告放在公用
    
    Node* root;

    BSTree() {
        root = nullptr;
    }
    
private: // 輸入和刪除單元的主要程式

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key) // 向樹裡地回尋找適合的位置
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }
    
    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->key) { // 此處同輸入向下遞迴尋找"目標"(k)
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            // 找到目標後的三種狀況
            if (!node->left && !node->right) { // 若目標是葉節點那直接刪除
                delete node;
                return nullptr;
            } else if (!node->left) { //---------- 這兩處是若有一個子結點的情況左右分開
                Node* temp = node->right;//    |
                delete node;//                 |
                return temp;//                 |
            } else if (!node->right) {//--------
                Node* temp = node->left;
                delete node;
                return temp;
            } else {// 最後是兩個子結點的情況
                Node* succ = node->right;
                while (succ->left)
                    succ = succ->left;
                node->key = succ->key;
                node->right = deleteNode(node->right, succ->key); //向下遞迴整理 刪除結點 的子結點
            }
      }

      return node;
    }
    
public:
    
    void deleteTree(Node* node) {
        if (node == nullptr) return;

        // Post-order traversal: delete children first
        deleteTree(node->left);
        deleteTree(node->right);
    
        delete node;
    }

    void clear() {
        deleteTree(root);
        root = nullptr;
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }
    
    int height(Node* root) {
    if (!root) return -1;
    return 1 + max(height(root->left), height(root->right));
    }

    void insertValue(int key) {
        root = insert(root, key);
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
        tree.clear(); 
    }
    
    return 0;
}
