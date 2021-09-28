#include "UndefinedStringAutomaton.h"

void UndefinedStringAutomaton::S0(const std::string& input) {
    if(!input.empty()) {
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
}

void UndefinedStringAutomaton::S1(const std::string& input) {
    if(input[index] == '\0'){
        inputRead++;
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '\n'){
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else if(input[index] != '\''){
        inputRead++;
        index++;
        S1(input);
    }
}

void UndefinedStringAutomaton::S2(const std::string& input){
    if (input[index] != '\''){
        Serr();
    }
    else if (input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
}