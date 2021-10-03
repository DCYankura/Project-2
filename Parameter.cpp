#include "Parameter.h"
Parameter::Parameter(std::string parameterString) {
    this->parameterString = parameterString;
}
std::string Parameter::parameterToSting() {
    return parameterString;
}