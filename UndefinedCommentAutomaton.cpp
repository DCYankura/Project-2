#include "UndefinedCommentAutomaton.h"

void UndefinedCommentAutomaton::S0(const std::string& input) {
    if(!input.empty()) {
        if (input[index] == '#') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
}

void UndefinedCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void UndefinedCommentAutomaton::S2(const std::string& input) {
    if (input[index] == '\0'){
        inputRead++;
    }
    else if (input[index] == '\n'){
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }
    else if (input[index] != '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else if(input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }
}

void UndefinedCommentAutomaton::S3(const std::string& input){
    if(input[index] == '#'){
        Serr();
    }
    else if (input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }
    else if (input[index] == '\n'){
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }
    else if (input[index] != '\0'){
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '\0'){
        inputRead++;
        index++;
    }
}