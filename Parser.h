//
// Created by danie on 9/27/2021.
//

#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Lexer.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include <vector>

class Parser{
private:
    int index;
    //include parameter vectors for facts, queries, and schemes
    //include rule vectors for rule
    //these vectors are used in parsePredicate and parseParameter to return vectors to parseScheme, parseFacts, parseQueries, and parseRules

    std::vector<Rule*> ruleList;
    std::vector<Predicate*> schemeList;
    std::vector<Predicate*> factList;
    std::vector<Predicate*> queryList;
    std::vector<Predicate*> predicateList;
    std::vector<Parameter*> parseParameterVector;
    std::vector<Parameter*> stringListVector;
    std::vector<Parameter*> IDListVector;
public:
    void parse(std::vector<Token*>);
    DatalogProgram* parseDatalogProgram(std::vector<Token*>);
    std::vector<Predicate*> parseSchemeList(std::vector<Token*>); //return list of predicates
    std::vector<Predicate*> parseFactList(std::vector<Token*>); // return list of predicates
    std::vector<Rule*> parseRuleList(std::vector<Token*>); //return list of rules
    std::vector<Predicate*> parseQueryList(std::vector<Token*>); //return list of predicates
    Predicate* parseScheme(std::vector<Token*>); //push schemeList onto datalog object
    Predicate* parseFact(std::vector<Token*>);
    Rule* parseRule(std::vector<Token*>);
    Predicate* parseQuery(std::vector<Token*>);
    Predicate* parseHeadPredicate(std::vector<Token*>);
    Predicate* parsePredicate(std::vector<Token*>);
    std::vector<Predicate*> parsePredicateList(std::vector<Token*>); //return list of predicates
    std::vector<Parameter*> parseParameterList(std::vector<Token*>); //Return list of parameters
    std::vector<Parameter*> parseStringList(std::vector<Token*>); //return vector of parameter objects
    std::vector<Parameter*> parseIdList(std::vector<Token*>); //return vector of parameter objects
    Parameter* parseParameter(std::vector<Token*> tokens);
    std::string match(TokenType type, std::vector<Token*> tokens);
    void checkForComment(std::vector<Token*> tokens);
};


#endif //PARSER_H
