#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

std::vector<std::string> order(int n, std::vector<std::string> &rules, std::string file){
    std::vector<std::string> orders;

    std::unordered_map<std::string, std::vector<std::string>> neighbors;
    std::unordered_map<std::string, int> count;

    for (int i=0; i < rules.size(); i++){
        std::stringstream ss(rules[i]);
        std::string listed;
        std::string dependent;
        ss >> listed;
        listed.pop_back();

        if(count.find(listed) == count.end()){
            count[listed]=0;
        } 

        while( ss >> dependent){
            neighbors[dependent].push_back(listed);
            count[listed]++;
        }
    }

    std::queue<std::string> q;
    q.push(file);
    std::unordered_map<std::string, bool> visited;
    visited[file] = true;

    while(!q.empty()){
        std::string current = q.front();
        q.pop();
        orders.push_back(current);

        for(int i =0; i < neighbors[current].size(); i++){
            if(!visited[neighbors[current][i]]){
                count[neighbors[current][i]]--;

                if(count[i] == 0){
                    q.push(neighbors[current][i]);
                    visited[neighbors[current][i]] = true;
                }
            }
        }
    }


    return orders;
}

int main(){
    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> rules(n);
    for (int i =0; i < n; i++){
        getline(std::cin, rules[i]);
    }

    std::string file;
    std::cin >> file;

    std::vector<std::string> fileOrders = order(n, rules, file);

    for (int i =0; i < fileOrders.size(); i++){
        std::cout << fileOrders[i] << "\n";
    }

    return 0;
}