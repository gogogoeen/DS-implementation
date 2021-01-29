#include <iostream>
#include <vector>
using namespace std;

// Heap is a data structure with finding the maximum element with O(1) time
// Use a vector to realize implement heap 
class heap {
public:
    heap(){};
    ~heap(){};
    void push(int key) {
        heapstore.push_back(key);
        swim(heapstore.size() - 1);
    }
    int top () {
        return heapstore[0];
    }
    void pop () {
        swap(heapstore[0], heapstore[heapstore.size() - 1]);
        heapstore.pop_back();
        sink(0);
    }

    bool isEmpty () {
        return heapstore.size() == 0;
    }

    void showHeap () {              //show heap with level
        int level = 1, ptr = 0;
        while (ptr < heapstore.size()) {
            for (int k = 1; k <= level; ++ k) {
                if (ptr == heapstore.size()) {cout << endl; return;}
                cout << heapstore[ptr ++];    
            }
            cout << endl;
            level *= 2;
        }
        return;
    }

private:
    void swim(int pos) {
        if (pos >= 1 && heapstore[pos] > heapstore[(pos + 1) / 2 - 1]) {
            swap(heapstore[pos], heapstore[(pos + 1) / 2 - 1]);
            swim((pos + 1) / 2 - 1);
        }
        return;
    }
    void sink(int pos) {
        if ((pos + 1) * 2 <= heapstore.size()) {
            int candidate = (pos + 1) * 2 - 1;
            if ((candidate + 1) <= heapstore.size() - 1)
                candidate = heapstore[candidate] > heapstore[candidate + 1] ? candidate : candidate + 1;
            if (heapstore[candidate] > heapstore[pos]) {
                swap(heapstore[pos], heapstore[candidate]);
                sink(candidate);
            }
        }
        return;
    }
    vector<int> heapstore;
};

int main() {
    heap myheap;
    cout << "tryinsert" << endl;
    myheap.push(1);
    myheap.showHeap();
    myheap.push(2);
    myheap.showHeap();
    myheap.push(3);
    myheap.showHeap();
    myheap.push(4);
    myheap.showHeap();
    myheap.push(5);
    myheap.showHeap();
    myheap.push(6);
    myheap.showHeap();
    myheap.push(7);
    myheap.showHeap();
    cout << "try pop" << endl;
    myheap.pop();
    myheap.showHeap();
    myheap.pop();
    myheap.showHeap();
    cout << "try get the element from the top" << endl;
    cout << myheap.top() << endl;
    

}