#include "DatalogProgram.h"

void DatalogProgram::OneToStringToRuleThemAll(){
    //std::cout << "in datalog toString" << std::endl;
    std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
    for(unsigned int i = 0; i < schemes.size(); i++){
        std::cout << ' ' << ' ';
        schemes[i]->predicateToString();
        std::cout << std::endl;
    }
    std::cout << "Facts(" << facts.size() << "):" << std::endl;
    for(unsigned int i = 0; i < facts.size(); i++){
        std::cout << ' ' << ' ';
        facts[i]->predicateToString();
        std::cout << "." << std::endl;
    }
    std::cout << "Rules(" << rules.size() << "):" << std::endl;
    std::cout << ' ' << ' ';
    for(unsigned int i = 0; i < rules.size(); i++){
        rules[i]->ruleToString();
        std::cout << "." << std::endl;
    }
    std::cout << "Queries(" << queries.size() << "):" << std::endl;
    for(unsigned int i = 0; i < queries.size(); i++){
        std::cout << ' ' << ' ';
        queries[i]->predicateToString();
        std::cout << "?" << std::endl;
    }
    creatDomain();
    std::cout << "Domain(" << Domain.size() << "):" << std::endl;
    for(auto it = Domain.begin(); it != Domain.end(); it++){
        if(std::next(it) == Domain.end()) {
            std::cout << ' ' << ' ' << *it;
        }
        else{
            std::cout << ' ' << ' ' << *it << std::endl;
        }
    }
}
void DatalogProgram::creatDomain() {
    for(unsigned int i = 0; i < facts.size(); i++){
        std::vector<std::string> temp;
        temp = facts[i]->getFactStrings();
        for(unsigned int j = 0; j < temp.size(); j++){
            Domain.insert(temp[j]);
        }
    }
}

std::vector<Predicate*> DatalogProgram::getSchemes() {
    return schemes;
}
std::vector<Predicate*> DatalogProgram::getFacts(){
    return facts;
}
std::vector<Predicate*> DatalogProgram::getQueries(){
    return  queries;
}
std::vector<Rule*> DatalogProgram::getRules(){
    return rules;
}