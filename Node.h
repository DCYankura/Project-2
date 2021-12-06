//
// Created by danie on 12/2/2021.
//

#ifndef NODE_H
#define NODE_H

#include <set>
class Node {
private:
    int ruleNum;
    //std::set<int> dependencies;
    bool visited;
    bool trivial;
public:
    Node(){};
    Node(int ruleNum, bool visited, bool trivial){
        this->ruleNum = ruleNum;
        //this->dependencies = dependencies;
        this->visited = visited;
        this->trivial = trivial;
    }
    int getRuleNumber(){
        return ruleNum;
    }
    /*
    std::set<int> getDependencies(){
        return dependencies;
    }
     */
    bool wasVisited(){
        return visited;
    }
    void visitNode(){
        visited = true;
    }
    void unVisit(){
        visited = false;
    }
    void notTrivial(){
        trivial = false;
    }
    bool isTrivial(){
        return trivial;
    }
};


#endif //NODE_H
