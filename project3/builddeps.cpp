#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

std::vector<std::string> order(int n, std::vector<std::string> &rules, std::string file){
    std::vector<std::string> orders;

    std::unordered_map<std::string, std::vector<std::string>> neighbors;
    std::unordered_map<std::string, int> count;

    std::set<std::string> files;

    for (int i=0; i < rules.size(); i++){
        std::stringstream ss(rules[i]);
        std::string listed;
        std::string dependent;
        ss >> listed;
        listed.pop_back();
        files.insert(listed);

        if(count.find(listed) == count.end()){
            count[listed]=0;
        } 

        while( ss >> dependent){
            neighbors[dependent].push_back(listed);
            count[listed]++;
            files.insert(dependent);
        }
    }

    std::queue<std::string> q;
    q.push(file);
    std::set<std::string> visited;
    visited.insert(file);

    while(!q.empty()){
        std::string current = q.front();
        q.pop();
        orders.push_back(current);

        for(int i =0; i < neighbors[current].size(); i++){
            if(visited.find(dependent) == visited.end()){
                count[dependent]--;
                if(count[dependent] == 0){
                    q.push[dependent];
                    visited.insert(dependent);
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