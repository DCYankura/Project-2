#include "Header.h"

Header::Header(std::vector<std::string> attributes) {
    // TODO: initialize all member variables
    this->attributes = attributes;
}

std::vector<std::string> Header::getAttributes() {
    return attributes;
}