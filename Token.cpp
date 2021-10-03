#include "Token.h"
#include <sstream>

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->description = std::move(description);
    this->line = line;
}
std::string Token::tokenTypeToString(TokenType type){
    switch (type){
        case TokenType::COLON: return "COLON";
        case TokenType::COLON_DASH: return "COLON_DASH";
        case TokenType::COMMA: return "COMMA";
        case TokenType::PERIOD: return "PERIOD";
        case TokenType::Q_MARK: return "Q_MARK";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::ADD: return "ADD";
        case TokenType::SCHEMES: return "SCHEMES";
        case TokenType::FACTS: return "FACTS";
        case TokenType::RULES: return "RULES";
        case TokenType::ID: return "ID";
        case TokenType::STRING: return "STRING";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::QUERIES: return "QUERIES";
        case TokenType::ENDOFFILE: return "EOF";
        case TokenType::UNDEFINEDCOMMENT: return "UNDEFINED";
        case TokenType::UNDEFINEDSTRING: return "UNDEFINED";
        case TokenType::UNDEFINED: return "UNDEFINED";
    }
    return "ERROR";
}
std::string Token::toString() {
    std::string typeName = Token::tokenTypeToString(type);
    std::stringstream ss;
    ss << "(" << typeName << ",\"" << description << "\"," << line << ")"<< std::endl;
    return ss.str();
}
std::string Token::getDescription() {
    return description;
}
TokenType Token::getType(){
    return type;
}
int Token::getLine(){
    return line;
}