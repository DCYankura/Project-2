//
// Created by danie on 10/26/2021.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
class Tuple
{
public:
    std::vector<std::string> values;
    bool operator< (const Tuple &rhs) const{
        return values < rhs.values;
    }
    Tuple(std::vector<std::string> values);
    std::vector<std::string> getValues();
};


#endif //TUPLE_H
