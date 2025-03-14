#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

std::vector<std::string> order(int n, std::vector<std::string> &rules, std::string file){
    std::vector<std::string> orders;

    std::unordered_map<std::string, std::vector<std::string>> dependencies;
    std::unordered_map<std::string, int> count;

    

    for (int i=0; i < n; i++){
        std::stringstream ss(rules[i]);
        std::string listed;
        ss >> listed;

        if(!listed.empty() && listed.back() == ':'){
            listed.pop_back();
        }
        
        if(count.find(listed) == count.end()){
            count[listed] = 0;
        }

        std::string dependency;
        while(ss >> dependency){
            dependencies[dependency].push_back(listed);
            count[listed]++;
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

        for(int i =0; i < dependencies[current].size(); i++){
            std::string dependent = dependencies[current][i];
            count[dependent]--;
            if(count[dependent] == 0){
                q.push(dependent);
                visited.insert(dependent);
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