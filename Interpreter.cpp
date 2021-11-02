//
// Created by danie on 10/31/2021.
//

#include "Interpreter.h"
Interpreter::Interpreter(DatalogProgram datalogProgram) {
    //populate database
    std::vector<Predicate*> s = datalogProgram.getSchemes();
    std::vector<Predicate*> f = datalogProgram.getFacts();
    std::vector<Predicate*> q = datalogProgram.getQueries();
    std::vector<Relation*> relationVector;
    for(unsigned int i = 0; i < s.size(); i++){
        Relation* newRelation = new Relation();
        std::string schemeName = s[i]->getID();
        std::vector<Parameter*> schemeParam = s[i]->getParameters();
        std::vector<std::string> schemeAttribute;
        for(unsigned int j = 0; j < schemeParam.size(); j++){
            schemeAttribute.push_back(schemeParam[j]->parameterToSting());
        }
        Header* newHeader = new Header(schemeAttribute);
        newRelation->setHeader(newHeader);
        newRelation->setName(schemeName);
        //relationVector.push_back(newRelation);
        //add straight to database
        for(unsigned int k = 0; k < f.size(); k++){
            std::string factName = f[k]->getID();
            if(factName == schemeName) {
                std::vector<Parameter *> factParam = f[k]->getParameters();
                std::vector<std::string> factAttributes;
                for (unsigned int l = 0; l < factParam.size(); l++) {
                    factAttributes.push_back(factParam[l]->parameterToSting());
                }
                Tuple newTuple = Tuple(factAttributes);
                newRelation->addTuple(newTuple);
            }
        }
        //add relation to db
        db.addRelation(schemeName, newRelation);
    }
    for(unsigned int i = 0; i < q.size(); i++){
        //get relation 'r' with same name as query 'q'
        Predicate tempPredicate = *q[i];
        Relation* r = evaluateQuery(tempPredicate);
        //print the resulting relation
        r->relationToString();
    }
}
Relation* Interpreter::evaluateQuery(Predicate &q) {
    std::string queryName = q.getID();
    //std::string queryName = q[i]->getID();
    std::map<std::string, Relation*> ImTheMap = db.getMap();
    Relation* r = ImTheMap[queryName];
    std::vector<Parameter*> param = q.getParameters();
    std::vector<std::string> paramStrings;
    //select for each constant in query 'q'
    std::vector<std::string> constants;
    std::vector<std::string> variables;
    std::vector<int> constIndices;
    std::vector<int> varIndices;
    bool repeat = false;
    //std::set<Tuple> newTuples;
    for(unsigned int i = 0; i < param.size(); i++){
        std::string temp = param[i]->parameterToSting();
        paramStrings.push_back(temp);
        if(temp[0] == '\''){
            //std::cout << "this is temp[0] " << temp[0] << " !!!!!" << std::endl;
            constants.push_back(temp);
            constIndices.push_back(i);
        }
        else{
            variables.push_back(temp);
            for(unsigned int j = 0; j < varIndices.size(); j++){
                if(temp == variables[j] && j != i){
                    repeat = true;
                }
            }
            if(!repeat) {
                varIndices.push_back(i);
            }
        }
    }
    for(unsigned int i = 0; i < constants.size(); i++){
        //std::cout << "this is the index: " << constIndices[i] << std::endl;
        //std::cout << "this is the constant: " << constants[i] << std::endl;
        r = r->select(constIndices[i],constants[i]);
    }
    //select for each pair of matching variables in 'q'
    if(variables.size() > 1) {
        for (unsigned int i = 0; i < paramStrings.size(); i++) {
            for (unsigned int j = 0; j < paramStrings.size(); j++){
                std::string temp1 = paramStrings[i];
                std::string temp2 = paramStrings[j];
                if(temp1 == temp2 && i != j && temp1[0] != '\''){
                    r = r->select(i,j);
                }
            }
        }
    }
    //make sure there are no duplicate variables in varIndices
    //project using the positions of the variables in 'q'
    //std::vector<int> varIndicesVec;
    //std::copy(varIndices.begin(), varIndices.end(), std::back_inserter(varIndicesVec));
    r = r->project(varIndices);
    //rename to match the names of the variables in 'q'
    r = r->rename(variables);
    std::cout << queryName << "(";
    for(unsigned int i = 0; i < paramStrings.size(); i++){
        if(i == paramStrings.size()-1){
            std::cout << paramStrings[i] << ")? ";
        }
        else{
            std::cout << paramStrings[i] << ",";
        }
    }
    return r;
}

/*
std::cout << "this is a test" << std::endl;
for(int i = 0; i < q.size(); i++){
    std::string queryName = q[i]->getID();
    std::vector<Parameter*> queryParam = q[i]->getParameters();
    std::vector<std::string> queryAttribute;
    for(int j = 0; j < queryParam.size(); j++){
        queryAttribute.push_back(queryParam[j]->parameterToSting());
    }
    std::cout << queryName << "(";
    for(int k = 0; k < queryAttribute.size(); k++){
        std::cout <<queryAttribute[k] << ", ";
    }
    std::cout << ")" << std::endl;
}
*/
/*
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
 */