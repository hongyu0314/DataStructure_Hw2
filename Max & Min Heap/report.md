# Max & Min Heap

## 解題說明

本題要求實現一個 Max/Min Heap。

### 解題策略

1. Max（Min） Heap: 插入進來的數值去跟父節點做比較，比父節點大（小）則交換，直到不能交換為止。

2. 刪除最大（小）節點之後把最後一個樹葉節點放到根節點，然後再進行 ( 1. )的 Heapify。

## 程式實作

以下為Max Heap的程式碼：

```cpp
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <sstream>

template <class T>
void ChangeSize1D(T*& a, int oldSize, int newSize) {
    if (newSize < 0) throw std::invalid_argument("new size must be >= 0");
    T* temp = new T[newSize];
    int number = std::min(oldSize, newSize);
    for (int i = 0; i < number; i++)
        temp[i] = a[i];
    delete[] a;
    a = temp;
}

template <class T>
class MaxHeap {
private:
    T* heap;          
    int heapSize;     
    int capacity;  

public:
    MaxHeap(int theCapacity = 10) {
        if (theCapacity < 1) throw std::invalid_argument("Capacity must be >= 1");
        capacity = theCapacity;
        heapSize = 0;
        heap = new T[capacity + 1];
    }

    ~MaxHeap() {
        delete[] heap;
    }

    bool IsEmpty() const {
        return heapSize == 0;
    }

    const T& Top() const {
        if (IsEmpty()) throw std::out_of_range("Heap is empty");
        return heap[1];
    }

    void Push(const T& e) {
        if (heapSize == capacity) {
            ChangeSize1D(heap, capacity + 1, 2 * capacity + 1);
            capacity *= 2;
        }

        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] < e) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = e;
    }

    void Pop() {
        if (IsEmpty()) throw std::out_of_range("Heap is empty");

        T maxItem = heap[1];
        T lastItem = heap[heapSize--];

        int parent = 1;
        int child = 2;

        while (child <= heapSize) {
            if (child < heapSize && heap[child] < heap[child + 1])
                child++;

            if (lastItem >= heap[child])
                break;

            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = lastItem;
    }
};

int main() {
    MaxHeap<double> mh;
    std::string line;
    std::cout << "指令： i X1 X2 ... Xn（插入多個數字）  p（刪除最大）  t（顯示最大）  q（離開）\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        char cmd;
        iss >> cmd;

        if (cmd == 'i') {
            double x;
            bool inserted = false;
            while (iss >> x) {
                mh.Push(x);
                std::cout << "已插入 " << x << "\n";
                inserted = true;
            }
            if (!inserted)
                std::cout << "格式錯誤，請輸入：i X1 X2 ... Xn\n";
        }
        else if (cmd == 'p') {
            if (!mh.IsEmpty()) {
                std::cout << "已刪除最大根節點 " << mh.Top() << "\n";
                mh.Pop();
            } else {
                std::cout << "Heap 目前為空，無法刪除。\n";
            }
        }
        else if (cmd == 't') {
            if (!mh.IsEmpty())
                std::cout << "目前最大根節點 = " << mh.Top() << "\n";
            else
                std::cout << "Heap 目前為空。\n";
        }
        else if (cmd == 'q') {
            std::cout << "剩餘（由大到小）：\n";
            while (!mh.IsEmpty()) {
                std::cout << mh.Top() << " ";
                mh.Pop();
            }
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "錯誤指令，請用 i /p /t /q。\n";
        }
    }

    return 0;
}
```
以下為Min Heap的程式碼：

```cpp
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <sstream>

template <class T>
void ChangeSize1D(T*& a, int oldSize, int newSize) {
    if (newSize < 0) throw std::invalid_argument("new size must be >= 0");
    T* temp = new T[newSize];
    int number = std::min(oldSize, newSize);
    for (int i = 0; i < number; i++)
        temp[i] = a[i];
    delete[] a;
    a = temp;
}

template <class T>
class MinHeap {
private:
    T* heap;
    int heapSize;
    int capacity;

public:
    MinHeap(int theCapacity = 10) {
        if (theCapacity < 1) throw std::invalid_argument("Capacity must be >= 1");
        capacity = theCapacity;
        heapSize = 0;
        heap = new T[capacity + 1];  // index 0 不用
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const {
        return heapSize == 0;
    }

    const T& Top() const {
        if (IsEmpty()) throw std::out_of_range("Heap is empty");
        return heap[1];
    }

    void Push(const T& e) {
        if (heapSize == capacity) {
            ChangeSize1D(heap, capacity + 1, 2 * capacity + 1);
            capacity *= 2;
        }

        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] > e) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = e;
    }

    void Pop() {
        if (IsEmpty()) throw std::out_of_range("Heap is empty");

        T lastItem = heap[heapSize--];
        int parent = 1;
        int child = 2;

        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (lastItem <= heap[child])
                break;
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = lastItem;
    }
};

int main() {
    MinHeap<double> mh;
    std::string line;
    std::cout << "指令： i X1 X2 ... Xn（插入多個數字）  p（刪除最小）  t（顯示最小）  q（離開）\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        char cmd;
        iss >> cmd;

        if (cmd == 'i') {
            double x;
            bool inserted = false;
            while (iss >> x) {
                mh.Push(x);
                std::cout << "已插入 " << x << "\n";
                inserted = true;
            }
            if (!inserted) {
                std::cout << "格式錯誤，請輸入：i X1 X2 ... Xn\n";
            }
        }
        else if (cmd == 'p') {
            if (!mh.IsEmpty()) {
                std::cout << "已刪除最小根節點 " << mh.Top() << "\n";
                mh.Pop();
            } else {
                std::cout << "Heap 目前為空，無法刪除。\n";
            }
        }
        else if (cmd == 't') {
            if (!mh.IsEmpty()) {
                std::cout << "目前最小根節點 = " << mh.Top() << "\n";
            } else {
                std::cout << "Heap 目前為空。\n";
            }
        }
        else if (cmd == 'q') {
            std::cout << "剩餘節點（由小到大）：\n";
            while (!mh.IsEmpty()) {
                std::cout << mh.Top() << " ";
                mh.Pop();
            }
            std::cout << "\n";
            break;
        }
        else {
            std::cout << "錯誤指令，請用 i/p/t/q。\n";
        }
    }
    return 0;
}
```
## 效能分析
     
時間複雜度： $O(logn)$。
 
空間複雜度： $O(n)$。


## 測試與驗證

### 測試案例
以Max Heap為例：

**i** : 插入數值

**t** : 印出根節點

**p** : 刪除根節點 

**q** : 退出且印出剩餘的數

| 測試案例 | 指令 | 結果 |
|----------|--------------|----------|
| 測試一   | i 6 7 8 10 12 14  | 6 7 8 10 12 14 |
| 測試二   | t  | 14 |
| 測試三   | p  | 刪除根節點 |
| 測試四   | q  | 12 10 8 7 6 |


## 申論及開發報告

### 在本程式中，使用Max/Min Heap的主要原因如下：

#### 時間效率高 
1. Top() 操作只需 $O(1)$，能取得最大／最小值。

#### 適用於動態資料
1. Heap 適合處理數值數量不固定且需要馬上調整順序的狀態。

2. 插入與刪除操作不用重新建整個結構。

#### 空間使用效率高
1. 使用陣列實作，節省記憶體，不需要指標連結節點（如樹結構）。

