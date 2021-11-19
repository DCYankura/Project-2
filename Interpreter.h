//
// Created by danie on 10/31/2021.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include <set>
//#include "Predicate.h"

class Interpreter {
private:
    Database db;
public:
    //Interpreter(){}
    Interpreter(DatalogProgram datalogProgram);
    Relation* evaluateQuery(Predicate& p);
    std::pair<Relation*, bool> evaluateRule(Rule* rule);
    Relation* evaluatePredicate(Predicate& p);
    //in constructor build database
};


#endif //INTERPRETER_H
