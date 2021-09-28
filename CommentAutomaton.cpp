#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
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

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2b(input);
    }
    else if(input[index] != '\n' && input[index] != '\0'){
        inputRead++;
        index++;
        S2a(input);
    }
}

void CommentAutomaton::S2a(const std::string& input){
    if (input[index] != '\n' && input[index] != '\0'){
        inputRead++;
        index++;
        S2a(input);
    }
}

void CommentAutomaton::S2b(const std::string& input) {
    if (input[index] == '\0'){
        Serr();
    }
    else if (input[index] == '\n'){
        inputRead++;
        index++;
        newLines++;
        S2b(input);
    }
    else if (input[index] != '|') {
        inputRead++;
        index++;
        S2b(input);
    }
    else if(input[index] == '|'){
        inputRead++;
        index++;
        S3b(input);
    }
    else if (input[index] == '\0'){
        /*
        Token* newToken = new Token(TokenType::UNDEFINED,input,newLines);
        tokens.push_back(newToken);
         */
        Serr();
    }
}

void CommentAutomaton::S3b(const std::string& input){
    if(input[index] == '#'){
        inputRead++;
    }
    else if (input[index] == '|'){
        inputRead++;
        index++;
        S3b(input);
    }
    else if (input[index] != '\0'){
        inputRead++;
        index++;
        S2b(input);
    }
    else if (input[index] == '\0'){
        Serr();
    }
}