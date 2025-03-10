#include <iostream>
#include <vector>


struct City{   
    int number = -1;
    int price = -1;
};

struct edge{
    int price;
    int to;
};

class minheap{
    private:
    std::vector<City> heap;

    void heapUp(int index){
        while(index > 0){
            int parent = (index - 1) /2;
            if (heap[index].price < heap[parent].price){
                City temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                index = parent;
            }else{
                break;
            }
        }
    }

    void heapDown(int index){
        int leftChild = index * 2 +1;
        int rightChild = index * 2 +2;
        int parent = index;

        if (leftChild < heap.size() && heap[leftChild].price < heap[parent].price){
            parent = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].price < heap[parent].price){
            parent = rightChild;
        }
        if (parent != index){
            City temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            heapDown(parent);
        }

    }

    public:

    void insert(City city){
        heap.push_back(city);
        heapUp(heap.size()-1);
    }

    City remove(){
        if (heap.empty()){
            return City();
        }
        City first = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()){
            heapDown(0);
        }
        return first;
    
    }

    bool empty() const{
        return heap.empty();
    }
};