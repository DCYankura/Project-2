#include "Tuple.h"
Tuple::Tuple(std::vector<std::string> values) {
    // TODO: initialize all member variables
    this->values = values;
}

std::vector<std::string> Tuple::getValues() {
    return values;
}