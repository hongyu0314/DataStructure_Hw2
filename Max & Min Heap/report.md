# Max & Min Heap

## 解題說明

本題要求實現一個 Max/Min Heap。

### 解題策略

1. Max（Min） Heap: 插入進來的數值去跟父節點做比較，比父節點大（小）則交換，直到不能交換為止。

2. 刪除最大（小）節點時把最後一個樹葉節點放到根節點，然後再進行 (1.)的 Heapify。

## 程式實作

以下為Max Heap的程式碼：

```cpp
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <sstream>

template <class T>
class MaxPQ {
public:
    virtual ~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MaxHeap : public MaxPQ<T> {
private:
    std::vector<T> heap;

    void swim(size_t k) { //和父節點比較誰比較大
        while (k > 0) {
            size_t parent = (k - 1) / 2;
            if (heap[parent] < heap[k]) { //比父節點大做交換
                std::swap(heap[parent], heap[k]);
                k = parent;
            }
            else break;
        }
    }

    void sink(size_t k) { //跟子節點比較
        size_t n = heap.size(); 
        while (2 * k + 1 < n) {
            size_t j = 2 * k + 1;       // 左子
            if (j + 1 < n && heap[j] < heap[j+1]) 
                j = j + 1;              // 改成較大的右子
            if (heap[k] < heap[j]) {
                std::swap(heap[k], heap[j]);
                k = j;
            }
            else break;
        }
    }

public:
    MaxHeap() = default;
    virtual ~MaxHeap() {}

    virtual bool IsEmpty() const override {
        return heap.empty();
    }

    virtual const T& Top() const override {
        if (heap.empty()) {
            throw std::out_of_range("MaxHeap::Top() called on empty heap");
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
    MaxHeap<double> mh;
    std::string line;
    std::cout << "指令： i X（插入 X）  p（刪除最大）  t（顯示最大）  q（離開）\n";

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
                int top = mh.Top();
                mh.Pop();
                std::cout << "已刪除最大節點 " << top << "\n";
            } else {
                std::cout << "Heap 目前為空，無法刪除。\n";
            }
        }
        else if (cmd == 't') {
            if (!mh.IsEmpty()) {
                std::cout << "目前最大節點 = " << mh.Top() << "\n";
            } else {
                std::cout << "Heap 目前為空。\n";
            }
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
            std::cout << "錯誤指令，請用 i /p/t/q。\n";
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
 
空間複雜度： $O(1)$。


## 測試與驗證

### 測試案例

| 測試案例 | 參數個數 $n$ | Average-case所耗時間 | Worst-case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 262 microseconds | 497 microseconds |
| 測試二   | $n = 1000$      | 696 microseconds | 1962 microseconds | 
| 測試三   | $n = 2000$      | 2721 microseconds | 9522 microseconds |
| 測試四   | $n = 3000$      | 7718 microseconds | 14336 microseconds |
| 測試五   | $n = 4000$      | 13504 microseconds | 29712 microseconds |
| 測試六   | $n = 5000$      | 22764 microseconds | 48361 microseconds |



## 申論及開發報告

### 在本程式中，使用插入排序法的主要原因如下：


