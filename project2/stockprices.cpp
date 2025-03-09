#include <iostream>
#include <vector>



struct Stock{
    int price;
    int shares;

    Stock(int p, int s): price(p), shares(s){

    }
};

struct input{
    std::string order_type;
    int shares;
    int price;
};

class minheap{
    private:
    std::vector<Stock> heap;

    void heapUp(int index){
        while(index > 0){
            int parent = (index - 1) /2;
            if (heap[index].price < heap[parent].price){
                Stock temp = heap[index];
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
            Stock temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            heapDown(parent);
        }

    }

    public:

    void insert(Stock stock){
        heap.push_back(stock);
        heapUp(heap.size()-1);
    }

    void remove(){
        if (!heap.empty()){
            heap[0] = heap.back();
            heap.pop_back();
            heapDown(0);
        }
    }

    bool empty(){
        return heap.empty();
    }

    Stock first(){
        if(!heap.empty()){
            return heap.front();
        }
        return Stock(-1,-1);
    }
};

class maxheap{
    private:
    std::vector<Stock> heap;

    void heapUp(int index){
        while(index > 0){
            int parent = (index - 1) /2;
            if (heap[index].price > heap[parent].price){
                Stock temp = heap[index];
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

        if (leftChild < heap.size() && heap[leftChild].price > heap[parent].price){
            parent = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].price > heap[parent].price){
            parent = rightChild;
        }
        if (parent != index){
            Stock temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            heapDown(parent);
        }

    }

    public:

    void insert(Stock stock){
        heap.push_back(stock);
        heapUp(heap.size()-1);
    }

    void remove(){
        if (!heap.empty()){
            heap[0] = heap.back();
            heap.pop_back();
            heapDown(0);
        }
    }

    bool empty(){
        return heap.empty();
    }

    Stock first(){
        if(!heap.empty()){
            return heap.front();
        }
        return Stock(-1,-1);
    }


};

void operation(int n, std::vector<input> stocks){
    maxheap buy;
    minheap sell;
    int stock_price = -1;

    for (const input &stock : stocks){

        if (stock.order_type == "buy"){
            buy.insert(Stock(stock.price, stock.shares));
        }
        else if (stock.order_type == "sell"){
            sell.insert(Stock(stock.price, stock.shares));
        }

        while (!buy.empty() && !sell.empty() && buy.first().price>= sell.first().price){
            Stock buying = buy.first();
            Stock selling = sell.first();
            buy.remove();
            sell.remove();

            int num_shares = std::min(buying.shares, selling.shares);
            stock_price = selling.price;

            if (buying.shares > num_shares) {
                buying.shares -= num_shares;
                buy.insert(buying);
            }

            if (selling.shares > num_shares){
                selling.shares -= num_shares;
                sell.insert(selling);
            }
        }

        std::string ask;
        if (sell.empty()){
            ask = "-";
        }
        else{
            ask = std::to_string(sell.first().price);
        }

        std::string bid;
        if (buy.empty()){
            bid = "-";
        }
        else{
            bid = std::to_string(buy.first().price);
        }

        std::string price_str;
        if (stock_price == -1){
            price_str = "-";
        }
        else{
            price_str = std::to_string(stock_price);
        }

        std::cout << ask << " " << bid << " " << price_str << "\n";
    }
}

int main(){

    int tests;
    std::cin >> tests;

    while (tests--){
        int transactions;
        std::cin >> transactions;
        std::vector<input> orders;

        for (int i=0; i< transactions; i++){
            std::string type;
            std::string space;
            int order_num;
            int order_price;
            std::cin >> type >> order_num >> space >> space>> order_price;

            orders.push_back({type, order_num, order_price});
        }
        operation(transactions, orders);

    }

    return 0;
}