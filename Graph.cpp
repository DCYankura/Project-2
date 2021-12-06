//
// Created by danie on 12/2/2021.
//

#include "Graph.h"
Graph::Graph(std::map<int, std::set<Node*>> dependencyMap) {
    this->dependencyMap = dependencyMap;
}

void Graph::GraphToString() {
    std::cout << "Dependency Graph" << std::endl;
    for(unsigned int i = 0; i < dependencyMap.size(); i++){
        std::set<int> dependencyInts = {};
        std::set<Node*> dependents = dependencyMap[i];
        for(auto it : dependents){
            dependencyInts.insert(it->getRuleNumber());
        }
        //std::set<Node*> dependents = dependencyMap[i];
        std::cout << "R" << i << ":";
        int k = 0;
        if(dependencyInts.size() == 0){
            std::cout << std::endl;
        }
        else {
            for(auto it: dependencyInts) {
                if(k == ((unsigned int)dependencyInts.size() - 1)) {
                    std::cout << "R" << it << std::endl;
                } else {
                    std::cout << "R" << it << ",";
                }
                k++;
            }
        }
    }
}