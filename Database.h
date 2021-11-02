//
// Created by danie on 10/26/2021.
//

#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"
#include <map>

class Database {
private:
    std::string name;
    std::map<std::string, Relation*> ImTheMap;
public:
    Database(){}
    Database(std::map<std::string, Relation*> ImTheMap);
    //create addRelation method
    void addRelation(std::string name, Relation* relation);
    std::map<std::string, Relation*> getMap(){
        return ImTheMap;
    }
};


#endif //DATABASE_H
