#include "IDAutomaton.h"
#include <cctype>

using namespace std;

void IDAutomaton::S0(const std::string& input) {
    if(input.size() > 0) {
        if (isalpha(input[index])) {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
}

void IDAutomaton::S1(const std::string& input) {
    if(!isspace(input[index]) && input[index] != '\0') {
        if (isalnum(input[index]) && !isspace(input[index+1]) && input[index+1] != '\0') {
            inputRead++;
            index++;
            S1(input);
        }
        else if(isalnum(input[index]) && (isspace(input[index+1]) || input[index+1] == '\0')){
            inputRead++;
        }
    }
}