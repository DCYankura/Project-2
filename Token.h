#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum class TokenType {
    COLON,
    COLON_DASH,
    // TODO: add the other types of tokens
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    ENDOFFILE,
    UNDEFINEDSTRING,
    UNDEFINEDCOMMENT,
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    //implement get functions for each variable and a toString function
    std::string toString();
    static std::string tokenTypeToString(TokenType type);
    std::string getDescription();
    TokenType getType();
    int getLine();
    // TODO: add other needed methods
};

#endif // TOKEN_H

