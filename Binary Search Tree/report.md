
# Binary Searching Tree

## 題目說明

題 1 要求實做一個 Binary Searching Tree 並加入 n 個節點，輸出要求該搜尋樹的 height/log₂n。

題 2 要求 delete key 的函式和效能分析 

## 測試與驗證

以下為執行結果 正如題目 height/log₂n 結果在 2 左右浮動。

![image](https://github.com/hongyu0314/DataStructure_Hw2/blob/main/img/BST_execute_outcome.png)

## 刪除結點實做

以下為刪除 Key(k) 的實作程式
```cpp
private: // 類別內部的主程式

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

public: // 外部程式對類別方法的 access

     void deleteKey(int key) {
        root = deleteNode(root, key);
    }
```

### 刪除結點效能分析

最差最差的情況下 需要走過每一個結點才能找到目標
也就是走過 n 個節點於是
時間複雜度(最差)： $O(n)$

## 申論及作業報告

### 在本程式中，使用 node 與 BSTree 使用 class 鏈結的主因如下：

1. 創建出的 BST 必不會是完整二元樹且平衡二元樹也不是 BST 的主軸

2. 相較於能適用陣列的 heap ， BST 並不太會更改值的位置

### 本次作業心得

平常沒有主動使用過 class 這次獲得了一個機會，對我而言玩新的方法十分的有趣又多了一種熟識的思路。
