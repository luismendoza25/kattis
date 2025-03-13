#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

std::vector<std::string> order(int n, std::vector<std::string> &rules, std::string file){

}

int main(){
    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string>> rules(n);
    for (int i =0; i < n; i++){
        getline(std::cin, rules[i]);
    }

    std::string file;
    std::cin >> file;

    std::vector<<std::string>> fileOrders = order(n, rules, file);

    for (int i =0; i < fileOrders.size(); i++){
        std::cout << fileOrders[i] << "\n";
    }

    return 0;
}