//
// Created by danie on 9/27/2021.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

class Parameter {
private:
    std::string parameterString;
public:
    Parameter(std::string parameterString);
    Parameter() {}
    //virtual ~Parameter() = default;
    std::string parameterToSting();
};


#endif //PARAMETER_H
