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
    std::map<std::string, Relation> ImTheMap;
public:
    Database(std::map<std::string, Relation> ImTheMap);
};


#endif //DATABASE_H
