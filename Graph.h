//
// Created by danie on 12/2/2021.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
class Graph {
private:
    std::map<int, std::set<Node*>> dependencyMap = {};
    //Node* ruleNode;
    std::set<Node*> dependencyList;
    int counter = 0;
public:
    Graph(){};
    Graph(std::map<int, std::set<Node*>> dependencyMap);
    /*
    Node* getNode(){
        return ruleNode;
    }
     */
    std::map<int, std::set<Node*>> getDependecyMap(){
        return dependencyMap;
    }
    std::set<Node*> getDependencyList(){
        return dependencyList;
    }
    std::map<int, std::set<Node*>> getMap(){
        return dependencyMap;
    }
    void addToMap(std::set<Node*> nodeList){
        dependencyMap.insert({counter, nodeList});
        counter = dependencyMap.size();
    }
    void GraphToString();
};


#endif //GRAPH_H
