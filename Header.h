//
// Created by danie on 10/26/2021.
//

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
class Header
{
private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<std::string> attributes);
    std::vector<std::string> getAttributes();
};


#endif //HEADER_H
