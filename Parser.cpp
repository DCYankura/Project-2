//
// Created by danie on 9/27/2021.
//

#include "Parser.h"

//objects for each class
void Parser::parse(std::vector<Token*> tokens) {
    try {
        auto* datalog = new DatalogProgram();
        datalog = parseDatalogProgram(tokens);
        std::cout << "Success!" << std::endl;
        datalog->OneToStringToRuleThemAll();
    }
    catch (Token* t){
        std::cout << "Failure!" << std::endl;
        std::cout << '\t' << "(" << t->tokenTypeToString(t->getType()) << ",\"" << t->getDescription() << "\"," << t->getLine() << ")";
    }
}
DatalogProgram*  Parser::parseDatalogProgram(std::vector<Token*> tokens){
    index = 0;
    auto* scheme = new Predicate();
    std::vector<Predicate*> schemeVector;
    //auto* fact = new Predicate();
    std::vector<Predicate*> factVector;
    auto* query = new Predicate();
    std::vector<Predicate*> queryVector;
    //auto* rule = new Rule();
    std::vector<Rule*> ruleVector;
    auto* datalog = new DatalogProgram(schemeVector, factVector, queryVector, ruleVector);
    checkForComment(tokens);
    match(TokenType::SCHEMES,tokens);
    match(TokenType::COLON,tokens);
    scheme = parseScheme(tokens);
    schemeVector = parseSchemeList(tokens);
    schemeVector.insert(schemeVector.begin(),scheme);
    match(TokenType::FACTS,tokens);
    match(TokenType::COLON,tokens);
    factVector = parseFactList(tokens);
    match(TokenType::RULES,tokens);
    match(TokenType::COLON,tokens);
    ruleVector = parseRuleList(tokens);
    match(TokenType::QUERIES,tokens);
    match(TokenType::COLON,tokens);
    query = parseQuery(tokens);
    queryVector = parseQueryList(tokens);
    queryVector.push_back(query);
    match(TokenType::ENDOFFILE,tokens);
    for(int i = 0; i < schemeVector.size(); i++){
        //auto* temp = new Predicate(schemeVector(i));
        datalog->addScheme(schemeVector[i]);
    }
    for(int i = 0; i < factVector.size(); i++){
        datalog->addFacts(factVector[i]);
    }
    for(int i = 0; i < ruleVector.size(); i++){
        datalog->addRules(ruleVector[i]);
    }
    for(int i = 0; i < queryVector.size(); i++){
        datalog->addQueries(queryVector[i]);
    }
    return datalog;
}
std::vector<Predicate*> Parser::parseSchemeList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Predicate*> tempList;
    if(tokens.at(index)->getType() == TokenType::ID) {
        auto* predicate = new Predicate();
        predicate = parseScheme(tokens);
        schemeList.push_back(predicate);
        tempList = parseSchemeList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            schemeList.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = schemeList;
    schemeList.clear();
    return tempList;
}
std::vector<Predicate*> Parser::parseFactList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Predicate*> tempList;
    if(tokens.at(index)->getType() == TokenType::ID){
        auto* predicate = new Predicate();
        predicate = parseFact(tokens);
        factList.push_back(predicate);
        tempList = parseFactList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            factList.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = factList;
    factList.clear();
    return tempList;
}
std::vector<Rule*> Parser::parseRuleList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Rule*> tempList;
    if(tokens.at(index)->getType() == TokenType::ID){
        auto* rule = new Rule();
        rule = parseRule(tokens);
        ruleList.push_back(rule);
        tempList = parseRuleList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            ruleList.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = ruleList;
    ruleList.clear();
    return tempList;
}
std::vector<Predicate*> Parser::parseQueryList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Predicate*> tempList;
    if(tokens.at(index)->getType() == TokenType::ID){
        auto* predicate = new Predicate();
        predicate = parseQuery(tokens);
        queryList.push_back(predicate);
        tempList = parseQueryList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            queryList.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = queryList;
    queryList.clear();
    return tempList;
}
Predicate* Parser::parseScheme(std::vector<Token*> tokens){
    //create predicate object for scheme
    std::vector<Parameter*> schemeList;
    checkForComment(tokens);
    std::string ID1 = match(TokenType::ID,tokens);
    match(TokenType::LEFT_PAREN,tokens);
    std::string ID2 = match(TokenType::ID,tokens);
    auto* temp = new Parameter(ID2);
    schemeList = parseIdList(tokens);
    schemeList.insert(schemeList.begin(),temp);
    match(TokenType::RIGHT_PAREN,tokens);
    //push object onto scheme vector
    auto* scheme = new Predicate(ID1, schemeList);
    return scheme;

}
Predicate* Parser::parseFact(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Parameter*> factList;
    std::string ID = match(TokenType::ID,tokens);
    match(TokenType::LEFT_PAREN,tokens);
    std::string tempString = match(TokenType::STRING,tokens);
    auto* temp = new Parameter(tempString);
    factList = parseStringList(tokens);
    factList.insert(factList.begin(),temp);
    match(TokenType::RIGHT_PAREN,tokens);
    match(TokenType::PERIOD,tokens);
    //return after making it not void
    auto* fact = new Predicate(ID, factList);
    return fact;
}
Rule* Parser::parseRule(std::vector<Token*> tokens){
    //create rule object
    auto* headPredicate = new Predicate();
    auto* predicate = new Predicate();
    std::vector<Predicate*> predicateList;
    checkForComment(tokens);
    std::vector<Rule*> ruleList;
    headPredicate = parseHeadPredicate(tokens);
    match(TokenType::COLON_DASH,tokens);
    predicate = parsePredicate(tokens);
    predicateList = parsePredicateList(tokens);
    predicateList.insert(predicateList.begin(),predicate);
    match(TokenType::PERIOD,tokens);
    auto* rule = new Rule(headPredicate, predicateList);
    return rule;
    //push rule object onto rule vector
}
Predicate* Parser::parseQuery(std::vector<Token*> tokens){
    auto* predicate = new Predicate();
    checkForComment(tokens);
    predicate = parsePredicate(tokens);
    match(TokenType::Q_MARK,tokens);
    return predicate;
}
Predicate* Parser::parseHeadPredicate(std::vector<Token*> tokens){
    std::string ID;
    std::string ID2;
    std::vector<Parameter*> parameterList;
    checkForComment(tokens);
    ID = match(TokenType::ID,tokens);
    match(TokenType::LEFT_PAREN,tokens);
    ID2 = match(TokenType::ID,tokens);
    auto* parameter = new Parameter(ID2);
    parameterList = parseIdList(tokens);
    parameterList.insert(parameterList.begin(),parameter);
    match(TokenType::RIGHT_PAREN,tokens);
    auto* predicate = new Predicate(ID, parameterList);
    return predicate;
}
Predicate* Parser::parsePredicate(std::vector<Token*> tokens){
    std::string ID;
    std::vector<Parameter*> parameterList;
    auto* parameter = new Parameter();
    checkForComment(tokens);
    ID = match(TokenType::ID,tokens);
    match(TokenType::LEFT_PAREN,tokens);
    parameter = parseParameter(tokens);
    parameterList = parseParameterList(tokens);
    parameterList.insert(parameterList.begin(),parameter);
    match(TokenType::RIGHT_PAREN,tokens);
    auto* predicate = new Predicate(ID, parameterList);
    return predicate;
}
std::vector<Predicate*> Parser::parsePredicateList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Predicate*> tempList;
    if(tokens.at(index)->getType() == TokenType::COMMA){
        match(TokenType::COMMA,tokens);
        auto* predicate = new Predicate();
        predicate = parsePredicate(tokens);
        predicateList.push_back(predicate);
        tempList = parsePredicateList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            predicateList.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = predicateList;
    predicateList.clear();
    return tempList;
}
std::vector<Parameter*> Parser::parseParameterList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Parameter*> tempList;
    if(tokens.at(index)->getType() == TokenType::COMMA){
        match(TokenType::COMMA,tokens);
        auto* parameter = new Parameter();
        parameter = parseParameter(tokens);
        parseParameterVector.push_back(parameter);
        tempList = parseParameterList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            parseParameterVector.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = parseParameterVector;
    parseParameterVector.clear();
    return tempList;
}
std::vector<Parameter*> Parser::parseStringList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Parameter*> tempList;
    if(tokens.at(index)->getType() == TokenType::COMMA){
        std::string tempString;
        match(TokenType::COMMA,tokens);
        tempString = match(TokenType::STRING,tokens);
        auto* newParameter = new Parameter(tempString);
        stringListVector.push_back(newParameter);
        tempList = parseStringList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            stringListVector.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = stringListVector;
    stringListVector.clear();
    return tempList;
}
std::vector<Parameter*> Parser::parseIdList(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::vector<Parameter*> tempList;
    if(tokens.at(index)->getType() == TokenType::COMMA){
        std::string IDString;
        match(TokenType::COMMA,tokens);
        IDString = match(TokenType::ID,tokens);
        auto* newParameter = new Parameter(IDString);
        IDListVector.push_back(newParameter);
        tempList = parseIdList(tokens);
        for(int i = 0; i < tempList.size(); i++){
            IDListVector.push_back(tempList[i]);
        }
    }
    //return after making it not void
    tempList = IDListVector;
    IDListVector.clear();
    return tempList;
}
Parameter* Parser::parseParameter(std::vector<Token*> tokens){
    checkForComment(tokens);
    std::string STRING;
    if(tokens.at(index)->getType() == TokenType::STRING){
        STRING = match(TokenType::STRING,tokens);
    }
    if(tokens.at(index)->getType() == TokenType::ID){
        STRING = match(TokenType::ID,tokens);
    }
    auto* parameter = new Parameter(STRING);
    return parameter;
    //return after making it not void
}
std::string Parser::match(TokenType type, std::vector<Token*> tokens) {
    checkForComment(tokens);
    auto* t = tokens.at(index);
    TokenType test = t->getType();
    TokenType test2 = type;
    std::string test3 = t->getDescription();
    if (t->getType() == type) {
        index++;
        std::string tempString = t->getDescription();
        return tempString;
    }
    else {
        throw t;
    }
}
void Parser::checkForComment(std::vector<Token*> tokens){
    if(tokens.at(index)->getType() == TokenType::COMMENT){
        index++;
    }
}
