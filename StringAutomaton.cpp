#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
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

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\0'){
        Serr();
    }
    else if (input[index] == '\n'){
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] != '\'' && input[index] != '\0') {
        inputRead++;
        index++;
        S1(input);
    }
    else{
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input){
    if (input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        //inputRead++;
    }
}