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
            std::cout << "剩餘：\n";
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


