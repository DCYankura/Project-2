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
public:
    void Interpret(DatalogProgram datalogProgram, Database database);
    Relation* evaluatePredicate(const Predicate& p);
};


#endif //INTERPRETER_H
