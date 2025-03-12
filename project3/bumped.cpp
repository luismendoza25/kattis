#include <iostream>
#include <vector>


struct City{   
    int number = -1;
    long long price = -1;
    bool flight = false;
};

struct Edge{
    long long price;
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
            return {-1,-1,false};
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


int minCost(int n, int m, int f, int s, int t, std::vector<std::vector<Edge>> &roads, std::vector<std::vector<Edge>> &flights){
    long long infinity = 1e15;
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(2, infinity));
    minheap heap;

    heap.insert({s, 0, false});
    dist[s][0] = 0;

    while(!heap.empty()){
        City current = heap.remove();

        if(current.number == t){
            return current.price;
        }


        int findex = 0;
        if(current.flight){
            findex = 1;
        }
        if(current.price > dist[current.number][findex]){
            continue;
        }

        if(current.number >= 0 && current.number < n){
            for (size_t i =0; i < roads[current.number].size(); i++){
                Edge edge = roads[current.number][i];
                long long addedPrice = current.price + edge.price;
                if (addedPrice < dist[edge.to][findex]){
                    dist[edge.to][findex] = addedPrice;
                    heap.insert({edge.to, addedPrice, current.flight});
                }
            }
        }

        if(current.number >= 0 && current.number < n){
            if(!current.flight){
                for (size_t j = 0; j < flights[current.number].size(); j++){
                    Edge plane = flights[current.number][j];
                    if(current.price <= dist[plane.to][1]){
                        dist[plane.to][1] = current.price;
                        heap.insert({plane.to, current.price, true});
                    }
                }
            }
        }
    }

    return infinity;
}

int main(){
    int n, m, f, s, t;
    std::cin >> n >> m >> f >> s >> t;

    std::vector<std::vector<Edge>> roads(n);
    std::vector<std::vector<Edge>> flights(n);

    for(int k =0; k < m; k ++){
        int i, j;
        long long c;
        std::cin >> i >> j >> c;
        roads[i].push_back(Edge{c, j});
        roads[j].push_back(Edge{c, i});
    }

    for (int p = 0; p < f; p++){
        int u, v;
        std::cin >> u >> v;
        flights[u].push_back(Edge{0,v});
    }
     

    std::cout << minCost(n, m,f, s, t, roads, flights);
}