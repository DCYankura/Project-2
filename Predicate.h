#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>
#include <string>
#include <vector>
#include "Parameter.h"
//Predicate class deals with schemes, facts, and queries
class Predicate {
protected:
    std::string ID;
    std::vector<Parameter*> parameters;
public:
    //virtual ~Predicate() = default;
    Predicate(std::string ID,std::vector<Parameter*> parameters) { this->ID = ID; this->parameters = parameters;}
    Predicate() {}
    void predicateToString();
    std::vector<std::string> getFactStrings();
    std::string getID();
    std::vector<Parameter*> getParameters();

};


#endif //PREDICATE_H
