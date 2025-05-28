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
