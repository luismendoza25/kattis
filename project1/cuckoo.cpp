#include <iostream>
#include <vector>


class my_set{
    private:
        std::vector<int> table;
        

    public:

        //checks if an element exists
        bool search(int key){
            for (int k : table){
                if (k == key){
                    return true;
                }
            }
            return false;
        }

        //insert used to track elements that have been visited
        void insert(int key){
            if (!search(key)){
                table.push_back(key);
            }

        }

        void clear(){
            table.clear();
        }

};

bool cuckoo(int m, int n, std::vector<std::pair<int, int>> &words){
    std::vector<int> table(n, -1);
    //my_set visited_words;

    if (m > n){
        return false;
    }

    for (int i = 0; i < m; i++){
        int word = i;
        int h1 = words[word].first;
        int h2 = words[word].second;

        my_set visited_words;
        

        if (h1 > n && h2 > n){
            return false;
        }


        for(int counts = 0; counts < n; counts++){
            if (table[h1] == -1){
                table[h1] = word; //insert into h1
                break;
            }
            else if(table[h2] == -1){
                table[h2] = word; //insert into h2
                break;
            }

            if (visited_words.search(word)){
                return false;
            }
        
            visited_words.insert(word);
            

            int evict = table[h1];
            table[h1] = word;
            word = evict;

            if (h1 == words[word].first) {
                h1 = words[word].second;
            } else {
                h1 = words[word].first;
            }

            if (table[h1] == -1) {
                table[h1] = word;
                break;
            }

        }

        if (visited_words.search(word)){
            return false;
        }

    }

    return true;

}


int main(){

    std::ios::sync_with_stdio(false); 
    std::cin.tie(NULL);

    int tests;
    std::cin >> tests;

    while(tests--){
        int m, n;
        std::cin >> m >> n;
        std::vector<std::pair<int, int>> words(m);

        for (int i = 0; i < m; i++) {
            std::cin >> words[i].first >> words[i].second;
        }

        if (cuckoo(m, n, words)) {
            std::cout << "successful hashing" << "\n";
        } else {
            std::cout << "rehash necessary" << "\n";
        }
    }

    return 0;

}