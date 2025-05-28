# Max & Min Heap

## 解題說明

本題要求實現一個 Max/Min Heap。

### 解題策略

1. Max（Min） Heap: 插入進來的數值去跟父節點做比較，比父節點大（小）則交換，直到不能交換為止。

2. 刪除最大（小）節點時把最後一個樹葉節點放到根節點，然後再進行 (1.)的 Heapify。

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
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <sstream>

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

    
    void swim(size_t k) { //和父節點比較誰比較小
        while (k > 0) {
            size_t parent = (k - 1) / 2;
            if (heap[parent] > heap[k]) { //比父節點小做交換
                std::swap(heap[parent], heap[k]);
                k = parent;
            }
            else break;
        }
    }

    void sink(size_t k) {
        size_t n = heap.size();
        while (2 * k + 1 < n) {
            size_t j = 2 * k + 1;
            if (j + 1 < n && heap[j] > heap[j+1])  
                j = j + 1;
            if (heap[k] > heap[j]) {  
                std::swap(heap[k], heap[j]);
                k = j;
            }
            else break;
        }
    }

public:
    MinHeap() = default;
    virtual ~MinHeap() {}

    virtual bool IsEmpty() const override {
        return heap.empty();
    }

    virtual const T& Top() const override {
        if (heap.empty()) {
            throw std::out_of_range("MinHeap::Top() called on empty heap");
        }
        return heap[0];
    }

    virtual void Push(const T& x) override {
        heap.push_back(x);
        swim(heap.size() - 1);
    }

    virtual void Pop() override {
        if (heap.empty()) return;
        std::swap(heap[0], heap.back());
        heap.pop_back();
        if (!heap.empty()) sink(0);
    }
};

int main() {
    MinHeap<double> mh;
    std::string line;
    std::cout << "指令： i X（插入 X）  p（刪除最小）  t（顯示最小）  q（離開）\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        char cmd;
        iss >> cmd;
        if (cmd == 'i') {
            double x;
            if (iss >> x) {
                mh.Push(x);
                std::cout << "已插入 " << x << "\n";
            } else {
                std::cout << "錯誤指令，請輸入：i X\n";
            }
        }
        else if (cmd == 'p') {
            if (!mh.IsEmpty()) {
                double top = mh.Top();
                mh.Pop();
                std::cout << "已刪除最小節點 " << top << "\n";
            } else {
                std::cout << "Heap 目前為空，無法刪除。\n";
            }
        }
        else if (cmd == 't') {
            if (!mh.IsEmpty()) {
                std::cout << "目前最小節點 = " << mh.Top() << "\n";
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
     
時間複雜度： $O(n²)$。
 
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

### 在本程式中，使用插入排序法的主要原因如下：


