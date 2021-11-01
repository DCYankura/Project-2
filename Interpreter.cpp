//
// Created by danie on 10/31/2021.
//

#include "Interpreter.h"
void Interpreter::Interpret(DatalogProgram datalogProgram, Database database) {
    std::vector<Predicate*> s = datalogProgram.getSchemes();
    std::vector<Predicate*> f = datalogProgram.getFacts();
    std::vector<Predicate*> q = datalogProgram.getQueries();
    std::vector<Relation*> relationVector;
    for(int i = 0; i < s.size(); i++){
        Relation* newRelation = new Relation();
        std::string name = s[i]->getID();
        std::vector<Parameter*> param = s[i]->getParameters();
        std::vector<std::string> attribute;
        for(int j = 0; j < param.size(); j++){
            attribute[j] = param[j]->parameterToSting();
        }
        Header* newHeader = new Header(attribute);
        newRelation->setHeader(newHeader);
        newRelation->setName(name);
        relationVector.push_back(newRelation);
    }
    for(int i = 0; i < f.size(); i++){
        std::string name = f[i]->getID();
        std::vector<Parameter*> param = f[i]->getParameters();
        std::vector<std::string> attributes;
        //std::set<Tuple> newTuples;
        for(int j = 0; j < param.size(); j++){
            attributes[j] = param[j]->parameterToSting();
        }
        Tuple newTuple = Tuple(attributes);
        for(int k = 0; k < relationVector.size(); i++){
            if(relationVector[i]->getName() == name){
                relationVector[i]->addTuple(newTuple);
            }
        }
    }
    /*
    for(int i = 0; i < q.size(); i++){
        //get relation 'r' with same name as query 'q'
        std::string name = q[i]->getID();
        Relation* r;
        for(int j = 0; j < relationVector.size(); j++){
            if(relationVector[j]->getName() == name){
                r = relationVector[j];
            }
        }
        //select for each constant in query 'q'

    }
     */
}
Relation* Interpreter::evaluatePredicate(const Predicate &p) {

}