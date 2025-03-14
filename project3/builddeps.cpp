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
    std::set<std::string> files;
    

    for (int i=0; i < n; i++){
        std::stringstream ss(rules[i]);
        std::string listed;
        ss >> listed;
        if(!listed.empty() && listed.back()==':'){
            listed.pop_back();
        }
        files.insert(listed);


        std::string dependency;
        while(ss >> dependency){
            dependencies[listed].push_back(dependency);
            count[dependency]++;
            files.insert(dependency);
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
            if(visited.find(dependent) == visited.end()){
                if(count.find(dependent) == count.end()){
                    count[dependent]=0;
                }
                count[dependent]--;
                if(count[dependent] == 0){
                    q.push(dependent);
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

    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> counts;
    std::unordered_map<std::string> files;

    for (int i = 0; i < n; i++){
        std::string line;
        std::string file;
        std::string dependency;

        std::getline(std::cin, line);

        size_t colon = line.find(':');
        file = line.substr(0, colon);
        files.insert(file);
        graph[file] = {};

        size_t next = colon + 2;
        while(next < line.size()){
            size_t space = line.find(' ', next);
            if (space == std::string::npos){
                space = line.size()
            }

            dependent = line.substr(next, space - next);
            graph[dependent].puh_back(file);
            counts.insert(dependency);

            next = space + 1;
        }
    }

    std::string recomp;
    std::cin >> recomp;
    std::vector<std::string> order = orders(graph, counts, recomp);

    for(int i = 0; i < order.size(); i++){
        std::cout << order[i] << "\n";
    }

    return 0;
}