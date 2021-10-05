#include "Rule.h"

void Rule::ruleToString() {
    headPredicate->predicateToString();
    std::cout << " :- ";
    for(unsigned int i = 0; i < predicateList.size(); i++){
        //std::cout << "(";
        if(i == predicateList.size() - 1) {
            predicateList[i]->predicateToString();
        }
        else{
            predicateList[i]->predicateToString();
            std::cout << ",";
        }
    }
}