#ifndef RULE_H
#define RULE_H
#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> predicateList;
public:
    Rule(Predicate* headPredicate,std::vector<Predicate*> predicateList) { this-> headPredicate = headPredicate; this-> predicateList = predicateList;}
    Rule() {}
    //virtual ~Rule() = default;
    void ruleToString();
    Predicate* getHeadPredicate(){
        return headPredicate;
    }
    std::vector<Predicate*> getPredicateList(){
        return predicateList;
    }
};


#endif //RULE_H
