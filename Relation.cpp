#include "Relation.h"
Relation::Relation(std::set<Tuple> tuples, std::string name, Header* headers) {
    this->tuples = tuples;
    this->name = name;
    this->headers = headers;
}
//TODO select, project, and rename need to return Relation objects
Relation* Relation::select(int index, std::string value){
//select rows in column index that equal value
    std::set<Tuple> newTuples;
    //std::vector<std::string> newHeaders;
    //std::vector<std::string> attributes = headers->getAttributes();
    std::set<Tuple>::iterator it;
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        if(tempValues[index] == value) {
            newTuples.insert(*it);
        }
    }
    Relation* newRelation = new Relation(newTuples, name, headers);
    return newRelation;
}

Relation* Relation::select(int column1, int column2) {
    //select rows for which values in column 1 = values in column 2
    std::set<Tuple> newTuples;
    //std::vector<std::string> newHeaders;
    //std::vector<std::string> attributes = headers->getAttributes();
    std::set<Tuple>::iterator it;
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        if(tempValues[column1] == tempValues[column2]) {
            newTuples.insert(*it);
        }
    }
    Relation* newRelation = new Relation(newTuples, name, headers);
    return newRelation;
}
Relation* Relation::project(std::vector<int> indices) {
    std::set<Tuple> newTuples;
    std::vector<std::string> newHeaders;
    std::vector<std::string> attributes = headers->getAttributes();
    //first for loop populates new header objects
    for(unsigned int i = 0; i < indices.size(); i++){
        //std::set<Tuple>::iterator it = tuples.begin();
        //std::advance(it,indices[i]);
        //newTuples.insert(*it);
        newHeaders.push_back(attributes[indices[i]]);
    }
    //second for loop iterates through set of tuples to create new set of tuples
    std::set<Tuple>::iterator it;
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        std::vector<std::string> newValues;
        for(unsigned int i = 0; i < indices.size(); i++){
            newValues.push_back(tempValues[indices[i]]);
        }
        Tuple tempTuple = Tuple(newValues);
        newTuples.insert(tempTuple);
    }
    Header* tempHeader = new Header(newHeaders);
    Relation* newRelation = new Relation(newTuples, name, tempHeader);
    return newRelation;
}
Relation* Relation::rename(std::vector<std::string> newAttributes) {
    Header* tempHeader =new Header(newAttributes);
    Relation* newRelation = new Relation(tuples, name, tempHeader);
    return newRelation;
}