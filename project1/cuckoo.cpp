#include <iostream>
#include <vector>
#include <unordered_set>


bool cuckoo(int n, std::vector<int> &table, int h1, int h2, int word){
    int maxswaps = n;
    std::unordered_set<int> visited;

    while(maxswaps--){
        if(table[h1] == -1){
            table[h1] = word;
            return true;
        }

        if(table[h1] == -1){
            table[h2] = word;
            return true;
        }
    

        int evicted = table[h1];
        table[h1] = word;

        if(visited.count(h1)){
            return false;
        }
        visited.insert(h1);
        word = evicted;
        int temp = h1;
        h1 =h2;
        h2 = temp;
    }
    return false;
}


int main(){
    int tests;
    std::cin >> tests;

    while(tests--){
        int m, n;
        std::cin >> m >> n;

        std::vector<int> table(n, -1);
        bool success = true;

        for(int i = 0; i < m; i++){
            int h1, h2;
            std::cin >> h1 >> h2;
            if(!cuckoo(n, table, h1, h2, i)){
                success = false;
            }
        }
        if(success){
            std::cout << "successful hashing" << "\n";
        }
        else{
            std::cout << "rehash necessary" << "\n";
        }
    }

    return 0;

}