#include <iostream>
#include "Lexer.h"
#include "StringAutomaton.h"
#include "AddAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "CommentAutomaton.h"
#include "FactsAutomaton.h"
#include "IDAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "QueriesAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "UndefinedCommentAutomaton.h"
#include "UndefinedStringAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    for (auto & a : automata) {
        delete a;
    }
    for (auto & a : tokens) {
        delete a;
    }
}
void Lexer::Print() {
    //std::cout << "printing" << std::endl;
    /*
    for(it = tokens.begin(); it != tokens.end(); it++){
        std::cout << (*it)->toString();
    }
     */
    for (auto & a : tokens){
       std::cout << a->toString();
    }
    std::cout << "Total Tokens = " << tokens.size();
}
void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UndefinedStringAutomaton());
    automata.push_back(new UndefinedCommentAutomaton());
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    int inputRead;

    //automata.at(0);
    while (!input.empty()) {
        int maxRead = 0;
        Automaton* maxAutomata = automata.at(0);
        //Check for whitespace
        while (!(input.empty()) && isspace(input[maxRead])) {
            if (input[maxRead] == '\n') {
                lineNumber++;
            }
            input = input.substr(maxRead + 1);
        }
        //checks to make sure string isn't empty
        if(input.empty()){
            break;
        }
        //Parallel part
        for(auto & i : automata){
            inputRead = i->Start(input);
            if(inputRead > maxRead){
                maxRead = inputRead;
                maxAutomata = i;
            }
        }
        //Max part of algorithm
        if(maxRead > 0){
            std::string tokenSubString = input.substr(0,maxRead);
            Token* newToken = maxAutomata->CreateToken(tokenSubString,lineNumber);
            lineNumber = lineNumber + maxAutomata->NewLinesRead();
            tokens.push_back(newToken);
        }
        else{
            //std::cout << "I'm in else now" << std::endl;
            maxRead = 1;
            std::string tokenSubString = input.substr(0,maxRead);
            auto* newToken = new Token(TokenType::UNDEFINED,tokenSubString,lineNumber);
            tokens.push_back(newToken);
        }
        input.erase(0,maxRead);
    }
    auto* newToken = new Token(TokenType::ENDOFFILE,"",lineNumber);
    tokens.push_back(newToken);
    //Lexer::Print();

    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

std::vector<Token*> Lexer::ReturnTokens() {
    return tokens;
}
