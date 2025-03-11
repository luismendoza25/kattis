#include <iostream>
#include <vector>


struct City{   
    int number = -1;
    int price = -1;
    bool flight = false;
};

struct Edge{
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


int minCost(int n, int m, int f, int s, int t, std::vector<std::vector<Edge>> &roads, std::vector<std::vector<Edge>> &flights){
    std::vector<std::vector<int> dist(n, std::vector<int>(2, 1e20));
    minheap heap;

    heap.insert({s, 0, false});
    dist[s][0] = 0;

    while(!heap.empty()){
        City current = heap.remove();
        if(current == t){
            return current.price();
        }
        if(current.price > dist[current.number][current.flight]){
            continue;
        }

        for (size_t i =0; i < roads[current.number]; i++){
            Edge edge = roads[current.number][i];
            int addedPrice = current.price + edge.price;
            if (addedPrice < dist[edge.to][current.flight]){
                dist[edge.to][current.flight] = addedPrice;
                heap.insert({edge.to, addedPrice, current.flight});
            }
        }

        if(!current.flight){
            for (size_t j = 0; j < flights[current.number].size(); j++){
                Edge plane = flights[current.number][j];
                if(current.cost < dist[plane.to][1]){
                    dist[flight.to][1] = current.cost;
                    heap.insert({flight.to, current.cost, true});
                }
            }
        }
    }

    return 1e20;
}

int main(){
    int n, m, f, s, t;
    std::cin >> n >> m >> f >> s >> t;

    std::vector<std::vector<Edge>> roads(n);
    std::vector<std::vector<Edge>> flights(n);

    for(int k =0; i < m; k ++){
        int i, j, c;
        std::cin >> i >> c >> j;
        roads[i].push_back({j, c});
        roads[j].push_back({i, c});
    }

    for (int i = 0; i < f; i++){
        int u, v;
        std::cin >> u >> v;
        roads[u].push_back({v,0});
    }
     

    std::cout << minCost(n, m,f, s, t, roads, flights);
}