//
// Created by danie on 9/27/2021.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram
{
protected:
    //make 4 vectors
    //Vector of Predicates for schemes
    std::vector<Predicate*> schemes;
    //vector of Predicates for the facts
    std::vector<Predicate*> facts;
    //vector of Predicates for the queries
    std::vector<Predicate*> queries;
    //vector of Rules for the rules
    std::vector<Rule*> rules;
    //vector for domain
    std::set<std::string> Domain;

public:
    DatalogProgram (std::vector<Predicate*> schemeVector, std::vector<Predicate*> factVector, std::vector<Predicate*> queryVector, std::vector<Rule*> ruleVector){
        schemes = schemeVector;
        facts = factVector;
        queries = queryVector;
        rules = ruleVector;
    }
    DatalogProgram(){}

    //explicit DatalogProgram(std::vector<Predicate*> schemes, std::vector<Predicate*> facts, std::vector<Predicate*> queries, std::vector<Rule*> rules) { this->schemes = schemes; this->facts = facts; this->queries = queries; this->rules = rules;}
    //make toString()
    //toString goes through parameters in fact predicates to print domain & create set<string?
    void addScheme(Predicate* predicate){
        schemes.push_back(predicate);
    }

    void addFacts(Predicate* predicate){
        facts.push_back(predicate);
    }

    void addQueries(Predicate* predicate){
        queries.push_back(predicate);
    }

    void addRules(Rule* rule){
        rules.push_back(rule);
    }

    void OneToStringToRuleThemAll();
    void creatDomain();
    std::vector<Predicate*> getSchemes();
    std::vector<Predicate*> getFacts();
    std::vector<Predicate*> getQueries();
    std::vector<Rule*> getRules();
};


#endif //DATALOGPROGRAM_H
