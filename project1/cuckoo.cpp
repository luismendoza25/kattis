#include <iostream>
#include <vector>
#include <unordered_set>


const int max = 10000;

bool insert(int word, int pos, std::vector<int> &table, const std::vector<std::pair<int, int>> &values, std::vector<bool> &visited){
    if (pos > max){
        return false;
    }

    int h1 = values[word].first;
    int h2 = values[word].second;

    if(table[h1] == -1){
        table[h1] = word;
        return true;
    }

    if(table[h2] == -1){
        table[h2] = word;
        return true;
    }

    if(!visited[table[h1]]){
        visited[table[h1]] = true;
        int evicted = table[h1];
        table[h1] = word;
        if(insert(evicted, pos+1, table, values, visited)){
            return true;
        }
        table[h1] = evicted;
        visited[evicted] = true;
    }

    if(!visited[table[h2]]){
        visited[table[h2]] = true;
        int evicted = table[h2];
        table[h2] = word;
        if(insert(evicted, pos+1, table, values, visited)){
            return true;
        }
        table[h2] = evicted;
        visited[evicted] = true;
    }

    return false;  


}

bool cuckoo(int m, int n, std::vector<std::pair<int, int>> &words) {
    std::vector<int> table(n, -1); 

    for(int i = 0; i < m; i++){
        std::vector<bool> visited(m, false);
        visited[i] = true;
        if(!insert(i, 0, table, words, visited)){
            return false;
        }
    }

    return true;
}


int main() {
    int tests;
    std::cin >> tests;

    while (tests--) {
        int m, n;
        std::cin >> m >> n;

        std::vector<std::pair<int, int>> words(m);
        for (int i = 0; i < m; i++) {
            std::cin >> words[i].first >> words[i].second;
        }

        if (cuckoo(m, n, words)) {
            std::cout << "successful hashing\n";
        } else {
            std::cout << "rehash necessary\n";
        }
    }

    return 0;
}
