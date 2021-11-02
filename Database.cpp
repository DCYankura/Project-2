//
// Created by danie on 10/26/2021.
//

#include "Database.h"
Database::Database(std::map<std::string, Relation*> ImTheMap) {
    this-> ImTheMap = ImTheMap;
}

//check with TA on these things
//1 what is the purpose of the database class
//2 for interpreter class, should I pass it a datalog object to get schemes, facts, and rules?
void Database::addRelation(std::string name, Relation* relation) {
    ImTheMap.insert({name, relation});
}