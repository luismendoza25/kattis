#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <algorithm>

void search(const std::string &file, const std::unordered_map<std::string, std::vector<std::string>> &graph, std::unordered_set<std::string> &visited, std::vector<std::string> &temp){
    visited.insert(file);

    if (graph.count(file)){
        const std::vector<std::string> &neighbors = graph.at(file);
        for (size_t i = 0; i < neighbors.size(); i++){
            const std::string &neighbor = neighbors[i];
            if(!visited.count(neighbor)){
                search(neighbor, graph, visited, temp);
            }
        }
    }
    temp.push_back(file);
}

std::vector<std::string> order(int n, std::vector<std::string> &rules, std::string refile){
    std::unordered_map<std::string, std::vector<std::string>> dependencies;
    std::unordered_map<std::string, std::vector<std::string>> tracking;
    
    for (int i=0; i < n; i++){
        std::stringstream ss(rules[i]);
        std::string listed;
        ss >> listed;

        if(!listed.empty() && listed.back() == ':'){
            listed.pop_back();
        }

        std::string dependency;
        while(ss >> dependency){
            dependencies[listed].push_back(dependency);
            tracking[dependency].push_back(listed);
        }
    }

    std::unordered_set<std::string> links;
    std::stack <std::string> stack;
    links.insert(refile);
    stack.push(refile);


    while(!stack.empty()){
        std::string current = stack.top();
        stack.pop();

        if (dependencies.count(current)){
            const std::vector<std::string> &dependents = dependencies[current];
            for(size_t i =0; i < dependents.size(); i++){
                const std::string &dep = dependents[i];
                if(!links.count(dep)){
                    links.insert(dep);
                    stack.push(dep);
                }
            }
        }
    }

    std::unordered_set<std::string> visited;
    std::vector<std::string> result;
    std::vector<std::string> vec(links.begin(), links.end());

    for(size_t i =0; i < vec.size(); i++){
        const std::string &file = vec[i];
        if(!visited.count(file)){
            search(file, tracking, visited, result);
        }
    }


    std::reverse(result.begin(), result.end());


    return result;
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