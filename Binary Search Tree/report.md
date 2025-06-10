
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

## 刪除結點效能分析

最差最差的情況下 需要走過每一個結點才能找到目標
也就是走過 n 個節點於是
時間複雜度(最差)： $O(n)$

## 申論及作業報告

### 在本程式中，使用Max/Min Heap的主要原因如下：

#### 時間效率高 
1. Top() 操作只需 $O(1)$，能取得最大／最小值。

#### 適用於動態資料
1. Heap 適合處理數值數量不固定且需要馬上調整順序的狀態。

2. 插入與刪除操作不用重新建整個結構。

#### 空間使用效率高
1. 使用陣列實作，節省記憶體，不需要指標連結節點（如樹結構）。
