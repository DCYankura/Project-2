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
#include <iostream>

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
    Relation* join(Relation* relationToJoin);
    Header* combineHeaders(Header* header1, Header* header2);
    bool isJoinable(Tuple tuple1, Tuple tuple2, std::vector<int> indicesT1, std::vector<int> indicesT2);
    Tuple combineTuple(Tuple tuple1, Tuple tuple2, std::vector<int> indicesT1, std::vector<int> indicesT2);
    bool unionize(Relation* &relationToJoin);
    std::string getName(){
        return name;
    }
    std::set<Tuple> &getTuples(){
        return tuples;
    }
    Header* getHeaders(){
        return headers;
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
    void relationToString();
};


#endif //RELATION_H
