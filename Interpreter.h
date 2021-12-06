//
// Created by danie on 10/31/2021.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include <algorithm>
#include <set>
//#include "Predicate.h"

class Interpreter {
private:
    Database db;
    Graph* forwardGraph;
    Graph* reverseGraph;
    std::vector<Node*> nodeRules;
    std::vector<int> postorderStack;
    std::vector<std::vector<int>> SCCs;
    std::vector<int> SCC;
    int counter;
public:
    //Interpreter(){}
    Interpreter(DatalogProgram datalogProgram);
    Relation* evaluateQuery(Predicate& p);
    std::pair<Relation*, bool> evaluateRule(Rule* rule);
    Relation* evaluatePredicate(Predicate& p);
    //make function that will evaluate a SCC
    bool evaluateSCCs(std::vector<Rule*> daRules, bool repeat, std::vector<int> tempSCC);
    //Make function that creates graph out of rules and then returns it
    void createForwardGraph(std::vector<Rule*> ruleList);
    void createReverseGraph(std::vector<Rule*> ruleList);
    Graph* getForwardGraph(){
        return forwardGraph;
    }
    Graph* getReverseGraph(){
        return reverseGraph;
    }
    std::vector<int> getPostOrder(){
        return postorderStack;
    }
    void DFSreverse(int startingNode);
    void DFSforward(int startingNode);
    void DFSFReverse(std::vector<Node*> ruleNodes);
    void DFSFForward(std::vector<int> order);
    //void checkForNonTrivial(std::vector<Rule*> rules);

    //in constructor build database
};


#endif //INTERPRETER_H
