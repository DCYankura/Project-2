#include <iostream>
//#include <string>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
//#include "Automaton.h"
//#include "Token.h"

using namespace std;

int main(__attribute__((unused)) int argc, char** argv) {

    auto* lexer = new Lexer();
    auto* parser = new Parser();

    // TODO
    //open file and use ifsteam.get() to parse through it
    string filename = argv[1];
    ifstream data(filename);
    string input;
    input.assign((std::istreambuf_iterator<char>(data) ),
                 (std::istreambuf_iterator<char>()) );

    lexer->Run(input);
    std::vector<Token*> tokens = lexer->ReturnTokens();
    parser->parse(tokens);
    delete lexer;

    return 0;
}