#include "DatalogProgram.h"

void DatalogProgram::OneToStringToRuleThemAll(){
    //std::cout << "in datalog toString" << std::endl;
    std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
    for(int i = 0; i < schemes.size(); i++){
        std::cout << '\t';
        schemes[i]->predicateToString();
        std::cout << "." << std::endl;
    }
    std::cout << "Facts(" << facts.size() << "):" << std::endl;
    for(int i = 0; i < facts.size(); i++){
        std::cout << '\t';
        facts[i]->predicateToString();
        std::cout << "." << std::endl;
    }
    std::cout << "Rules(" << rules.size() << "):" << std::endl;
    std::cout << '\t';
    for(int i = 0; i < rules.size(); i++){
        rules[i]->ruleToString();
        std::cout << "." << std::endl;
    }
    std::cout << "Queries(" << queries.size() << "):" << std::endl;
    for(int i = 0; i < queries.size(); i++){
        std::cout << '\t';
        queries[i]->predicateToString();
        std::cout << "?" << std::endl;
    }
    creatDomain();
    std::cout << "Domain(" << Domain.size() << "):" << std::endl;
    for(auto it = Domain.begin(); it != Domain.end(); it++){
        std::cout << '\t' << *it << std::endl;
    }
}
void DatalogProgram::creatDomain() {
    for(int i = 0; i < facts.size(); i++){
        std::vector<std::string> temp;
        temp = facts[i]->getFactStrings();
        for(int i = 0; i < temp.size(); i++){
            Domain.insert(temp[i]);
        }
    }
}