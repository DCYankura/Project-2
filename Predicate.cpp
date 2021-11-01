#include "Predicate.h"
void Predicate::predicateToString() {
    std::cout << ID << "(";
    for(unsigned int i = 0; i < parameters.size(); i++){
        std::string parameterString = parameters[i]->parameterToSting();
        if(i == parameters.size() - 1){
            std::cout << parameterString;
        }
        else{
            std::cout << parameterString << ",";
        }
    }
    std::cout << ")";
}
std::vector<std::string> Predicate::getFactStrings() {
    std::vector<std::string> temp;
    for(unsigned int i = 0; i < parameters.size(); i++){
        std::string parameterString = parameters[i]->parameterToSting();
        temp.push_back(parameterString);
    }
    return temp;
}
std::string Predicate::getID() {
    return ID;
}
std::vector<Parameter*> Predicate::getParameters() {
    return parameters;
}