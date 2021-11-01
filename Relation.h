//
// Created by danie on 10/26/2021.
//

#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <vector>
#include <string>
#include <set>

class Relation
{
private:
    std::string name;
    std::set<Tuple> tuples;
    Header* headers;
public:
    Relation(){}
    Relation(std::set<Tuple> tuples, std::string name, Header* headers);
    Relation* select(int index, std::string value);
    Relation* select(int column1, int column2);
    Relation* project(std::vector<int> indices);
    Relation* rename(std::vector<std::string> newAttributes);
    std::string getName(){
        return name;
    }
    std::set<Tuple> getTuples(){
        return tuples;
    }
    void addTuple(Tuple newTuple){
        tuples.insert(newTuple);
    }
    void setName(std::string name){
        this->name = name;
    }
    void setTuples(std::set<Tuple> tuples){
        this->tuples = tuples;
    }
    void setHeader(Header* headers){
        this->headers = headers;
    }
};


#endif //RELATION_H
