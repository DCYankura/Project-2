//
// Created by danie on 10/31/2021.
//

#include "Interpreter.h"
Interpreter::Interpreter(DatalogProgram datalogProgram) {
    //populate database
    std::vector<Predicate*> s = datalogProgram.getSchemes();
    std::vector<Predicate*> f = datalogProgram.getFacts();
    std::vector<Predicate*> q = datalogProgram.getQueries();
    std::vector<Relation*> relationVector;
    for(unsigned int i = 0; i < s.size(); i++){
        Relation* newRelation = new Relation();
        std::string schemeName = s[i]->getID();
        std::vector<Parameter*> schemeParam = s[i]->getParameters();
        std::vector<std::string> schemeAttribute;
        for(unsigned int j = 0; j < schemeParam.size(); j++){
            schemeAttribute.push_back(schemeParam[j]->parameterToSting());
        }
        Header* newHeader = new Header(schemeAttribute);
        newRelation->setHeader(newHeader);
        newRelation->setName(schemeName);
        //relationVector.push_back(newRelation);
        //add straight to database
        for(unsigned int k = 0; k < f.size(); k++){
            std::string factName = f[k]->getID();
            if(factName == schemeName) {
                std::vector<Parameter *> factParam = f[k]->getParameters();
                std::vector<std::string> factAttributes;
                for (unsigned int l = 0; l < factParam.size(); l++) {
                    factAttributes.push_back(factParam[l]->parameterToSting());
                }
                Tuple newTuple = Tuple(factAttributes);
                newRelation->addTuple(newTuple);
            }
        }
        //add relation to db
        db.addRelation(schemeName, newRelation);
    }
    //create forward and reverse graphs, and find SCCs
    std::vector<Rule*> daRules = datalogProgram.getRules();
    createForwardGraph(daRules);
    createReverseGraph(daRules);
    forwardGraph->GraphToString();
    //reverseGraph->GraphToString();
    DFSFReverse(nodeRules);
    std::vector<int> postOrder = postorderStack;
    std::reverse(postOrder.begin(), postOrder.end());
    DFSFForward(postOrder);
    //evaluate rules
    //Relation* ruleRelation = new Relation();
    std::cout << "Rule Evaluation" << std::endl;
    bool repeat = true;
    //std::pair<Relation*, bool> rulePair = std::make_pair(ruleRelation, repeat);
    for(unsigned int i = 0; i < SCCs.size(); i++) {
        std::vector<int> tempSCC = SCCs[i];
        std::set<int> SCCInts = {};
        for(unsigned int j = 0; j < tempSCC.size(); j++){
            SCCInts.insert(tempSCC[j]);
        }
        counter = 0;
        bool trivial = true;
        repeat = true;
        for(unsigned int j = 0; j < tempSCC.size(); j++){
            if(!nodeRules[tempSCC[j]]->isTrivial()){
                trivial = false;
            }
        }
        std::cout << "SCC: ";
        int index = 0;
        for (auto it : SCCInts){
            if(index == ((unsigned int)tempSCC.size()-1)) {
                std::cout << "R" << it << std::endl;
            }
            else{
                std::cout << "R" << it << ",";
            }
            index++;
        }
        if(SCCs[i].size() > 1 || !trivial) {
            while(repeat) {
                repeat = evaluateSCCs(daRules, repeat, tempSCC);
            }
        }
        else{
            evaluateSCCs(daRules, repeat, tempSCC);
        }
        std::cout << counter << " passes: ";
        index = 0;
        for (auto it : SCCInts){
            if(index == ((unsigned int)tempSCC.size()-1)) {
                std::cout << "R" << it << std::endl;
            }
            else{
                std::cout << "R" << it << ",";
            }
            index++;
        }
    }
        /*
        repeat = false;
        for (unsigned int i = 0; i < daRules.size(); i++) {
            daRules[i]->ruleToString();
            std::cout << "." << std::endl;
            rulePair = evaluateRule(daRules[i]);
            ruleRelation = rulePair.first;
            bool repeatTemp = rulePair.second;
            if(!repeat){
                repeat = repeatTemp;
            }
            std::string nameToMatch = ruleRelation->getName();
            //(db.getMap())[nameToMatch] = ruleRelation;
            Header *ruleHeaders = ruleRelation->getHeaders();
            std::vector<std::string> attributes = ruleHeaders->getAttributes();
            std::set<Tuple> tupleSet = ruleRelation->getTuples();
            std::set<Tuple>::iterator it;
        }
        counter++;
         */
    //std::cout << std::endl << "Schemes populated after " << counter << " passes through the Rules." << std::endl << std::endl;
    std::cout << std::endl << "Query Evaluation" << std::endl;
    for(unsigned int i = 0; i < q.size(); i++){
        //get relation 'r' with same name as query 'q'
        Predicate tempPredicate = *q[i];
        Relation* r = evaluateQuery(tempPredicate);
        //print the resulting relation
        r->relationToString();
    }
}

bool Interpreter::evaluateSCCs(std::vector<Rule *> daRules, bool repeat, std::vector<int> tempSCC){
    repeat = false;
    for(unsigned int i = 0; i < tempSCC.size(); i++) {
        int index = tempSCC[i];
        /*
        bool trivial = false;
        std::set<Node*> dependencies = forwardGraph->getDependecyMap()[index];
        std::string head = daRules[index]->getHeadPredicate()->getID();
        for(auto it : dependencies){
            std::string predicateID = daRules[it*]
            if()
        }
         */
        daRules[index]->ruleToString();
        std::cout << "." << std::endl;
        std::pair<Relation*, bool> rulePair = evaluateRule(daRules[index]);
        Relation* ruleRelation = new Relation();
        ruleRelation = rulePair.first;
        bool repeatTemp = rulePair.second;
        if(!repeat){
            repeat = repeatTemp;
        }
        std::string nameToMatch = ruleRelation->getName();
        //(db.getMap())[nameToMatch] = ruleRelation;
        Header *ruleHeaders = ruleRelation->getHeaders();
        std::vector<std::string> attributes = ruleHeaders->getAttributes();
        std::set<Tuple> tupleSet = ruleRelation->getTuples();
        //std::set<Tuple>::iterator it;
    }
    counter++;
    return repeat;
}

void Interpreter::createForwardGraph(std::vector<Rule*> ruleList) {
    this->forwardGraph = new Graph();
    //std::vector<Node*> nodeList;
    for(unsigned int i = 0; i < ruleList.size(); i++){
        Node* newNode = new Node(i, false, true);
        nodeRules.push_back(newNode);
    }
    //Graph* newGraph = new Graph();
    //std::map<int, std::set<Node*>> newMap = newGraph->getMap();

    /*
    for(int i = 0; i < ruleList.size(); i++){
        std::string headName = ruleList[i]->getHeadPredicate()->getID();
        //Node* newNode = new Node(i, false);
        std::set<Node*> dependencySet = {};
        for(int j = 0; j < ruleList.size(); j++){
            for(int k = 0; k < ruleList[j]->getPredicateList().size(); k++){
                std::string predicateName = ruleList[j]->getPredicateList()[k]->getID();
                if(predicateName == headName){
                    dependencySet.insert(nodeList[j]);
                }
            }
        }
        forwardGraph->addToMap(dependencySet);
    }
     */

    for(unsigned int i = 0; i < ruleList.size(); i++){
        std::set<Node*> dependencySet = {};
        for(unsigned int k = 0; k < ruleList[i]->getPredicateList().size(); k++){
            std::string headName = ruleList[i]->getPredicateList()[k]->getID();
            for(unsigned int j = 0; j < ruleList.size(); j++){
                std::string predicateName = ruleList[j]->getHeadPredicate()->getID();
                if(headName == predicateName){
                    dependencySet.insert(nodeRules[j]);
                }
            }
        }
        forwardGraph->addToMap(dependencySet);
    }
}

void Interpreter::createReverseGraph(std::vector<Rule*> ruleList) {
    this->reverseGraph = new Graph();
    //Graph* newGraph = new Graph();
    //std::map<int, std::set<Node*>> newMap = newGraph->getMap();
    //std::vector<Node*> nodeList;
    /*
    for(int i = 0; i < ruleList.size(); i++){
        Node* newNode = new Node(i, false);
        nodeList.push_back(newNode);
    }
     */
    for(unsigned int i = 0; i < ruleList.size(); i++){
        std::string headName = ruleList[i]->getHeadPredicate()->getID();
        std::set<Node*> dependencySet = {};
        for(unsigned int j = 0; j < ruleList.size(); j++){
            for(unsigned int k = 0; k < ruleList[j]->getPredicateList().size(); k++){
                std::string predicateName = ruleList[j]->getPredicateList()[k]->getID();
                if(predicateName == headName){
                    dependencySet.insert(nodeRules[j]);
                    if(i==j){
                        nodeRules[i]->notTrivial();
                    }
                }
            }
        }
        reverseGraph->addToMap(dependencySet);
    }
}

void Interpreter::DFSreverse(int startingNode) {
    nodeRules[startingNode]->visitNode();
    std::set<Node*> adjacencyList = reverseGraph->getDependecyMap()[startingNode];
    std::vector<Node*> adjacencyVector;
    for(auto it : adjacencyList){
        adjacencyVector.push_back(it);
    }
    for(unsigned int i = 0; i < adjacencyVector.size(); i++){
        if(!adjacencyVector[i]->wasVisited()){
            int nodeToVisit = adjacencyVector[i]->getRuleNumber();
            DFSreverse(nodeToVisit);
            //postorderStack.push_back(startingNode);
        }
    }
    postorderStack.push_back(startingNode);
    //SCC.insert(startingNode);
}

void Interpreter::DFSforward(int startingNode) {
    nodeRules[startingNode]->visitNode();
    std::set<Node*> adjacencyList = forwardGraph->getDependecyMap()[startingNode];
    std::vector<Node*> adjacencyVector;
    for(auto it : adjacencyList){
        adjacencyVector.push_back(it);
    }
    for(unsigned int i = 0; i < adjacencyVector.size(); i++){
        if(!adjacencyVector[i]->wasVisited()){
            int nodeToVisit = adjacencyVector[i]->getRuleNumber();
            DFSforward(nodeToVisit);
            //postorderStack.push_back(startingNode);
        }
    }
    //postorderStack.push_back(startingNode);
    SCC.push_back(startingNode);
}

void Interpreter::DFSFReverse(std::vector<Node*> ruleNodes) {
    //Need to loop through reverse graph.
    for(unsigned int i = 0; i < ruleNodes.size(); i++){
        if(!ruleNodes[i]->wasVisited()){
            DFSreverse(i);
        }
    }
}

void Interpreter::DFSFForward(std::vector<int> order) {
    //SCCs = {};
    //SCC = {};
    for(unsigned int i = 0; i < nodeRules.size(); i++){
        nodeRules[i]->unVisit();
    }
    for(unsigned int i = 0; i < order.size(); i++){
        if(!nodeRules[order[i]]->wasVisited()){
            DFSforward(order[i]);
            SCCs.push_back(SCC);
            SCC = {};
        }
    }
    //SCC = {};
}

std::pair<Relation*, bool> Interpreter::evaluateRule(Rule* rule) {
    //std::vector<Rule*> daRules = datalogProgram.getRules();
    std::vector<Relation*> relationList;
    //Relation* relationToReturn = new Relation();
    //step 1: evaluate predicates on right-hand side of rules
    std::vector<Predicate*> predicateList = rule->getPredicateList();
    for(unsigned int j = 0; j < predicateList.size(); j++){
        //evaluate rules using evaluateQuery function and add them to vector
        Relation* ruleRelation = evaluatePredicate(*predicateList[j]);
        relationList.push_back(ruleRelation);
    }
    //step 2: Join relations in relationList
    Relation* tempRelation = relationList[0];
    if(relationList.size() > 0){
        for(unsigned int k = 1; k < relationList.size(); k++){
            tempRelation = tempRelation->join(relationList[k]);
        }
    }
    //step 3: project the columns that appear in the head predicate
    Predicate* tempHeadPredicate = rule->getHeadPredicate();
    std::vector<Parameter*> tempHeadParam = tempHeadPredicate->getParameters();
    Header* tempRelationHeader = tempRelation->getHeaders();
    std::vector<std::string> tempRelationValues = tempRelationHeader->getAttributes();
    std::vector<int> headPredicateIndices;
    for(unsigned int k = 0; k < tempHeadParam.size(); k++){
        for(unsigned int l = 0; l < tempRelationValues.size(); l++){
            if(tempHeadParam[k]->parameterToSting() == tempRelationValues[l]){
                headPredicateIndices.push_back(l);
            }
        }
    }
    tempRelation = tempRelation->project(headPredicateIndices);
    //Step 4: rename tempRelation to match attributes in scheme with same ID
    std::string nameToMatch = (rule->getHeadPredicate())->getID();
    std::map<std::string, Relation*> ImTheMap = db.getMap();
    Relation* dbRelation = ImTheMap[nameToMatch];
    //need to get right name to match with
    Header* headersToMatch = dbRelation->getHeaders();
    std::vector<std::string> attributesToMatch = headersToMatch->getAttributes();
    //std::vector<Predicate*> schemeVector = datalogProgram.getSchemes();
    //std::vector<Parameter*> tempAttributes;
    //std::vector<std::string> matchingAttributes;
    /*
    for(int k = 0; k < schemeVector.size(); k++){
        if(schemeVector[k]->getID() == tempRelation->getName()){
            tempAttributes = schemeVector[k]->getParameters();
        }
    }

    for(int k = 0; k < matchingAttributes.size(); k++){
        matchingAttributes.push_back(tempAttributes[k]->parameterToSting());
    }
     */
    tempRelation = tempRelation->rename(attributesToMatch);

    //Step 5: union tempRelation and relation in DB
    //get relation from database that has the same name as relationToJoin
    std::string nameToJoin = tempRelation->getName();
    //std::map<std::string, Relation*> ImTheMap = db.getMap();
    Relation* dbRelationUnion = ImTheMap[nameToMatch];
    bool updated = tempRelation->unionize(dbRelationUnion);
    std::pair<Relation*, bool> returnPair = std::make_pair(tempRelation, updated);
    Database tempdb = db;
    return returnPair;
}

Relation* Interpreter::evaluateQuery(Predicate &q) {
    std::string queryName = q.getID();
    //std::string queryName = q[i]->getID();
    std::map<std::string, Relation*> ImTheMap = db.getMap();
    Relation* r = ImTheMap[queryName];
    std::vector<Parameter*> param = q.getParameters();
    std::vector<std::string> paramStrings;
    //select for each constant in query 'q'
    std::vector<std::string> constants;
    std::vector<std::string> variables;
    std::vector<std::string> varNoRepeats;
    std::vector<int> constIndices;
    std::vector<int> varIndices;
    //std::set<Tuple> newTuples;
    for(unsigned int i = 0; i < param.size(); i++){
        std::string temp = param[i]->parameterToSting();
        paramStrings.push_back(temp);
        bool repeat = false;
        if(temp[0] == '\''){
            //std::cout << "this is temp[0] " << temp[0] << " !!!!!" << std::endl;
            constants.push_back(temp);
            constIndices.push_back(i);
        }
        else{
            variables.push_back(temp);
            for(unsigned int j = 0; j < varIndices.size(); j++){
                if(temp == variables[j] && j != i){
                    repeat = true;
                }
            }
            if(!repeat) {
                varIndices.push_back(i);
                varNoRepeats.push_back(temp);
            }
        }
    }
    for(unsigned int i = 0; i < constants.size(); i++){
        //std::cout << "this is the index: " << constIndices[i] << std::endl;
        //std::cout << "this is the constant: " << constants[i] << std::endl;
        r = r->select(constIndices[i],constants[i]);
    }
    //select for each pair of matching variables in 'q'
    if(variables.size() > 1) {
        for (unsigned int i = 0; i < paramStrings.size(); i++) {
            for (unsigned int j = 0; j < paramStrings.size(); j++){
                std::string temp1 = paramStrings[i];
                std::string temp2 = paramStrings[j];
                if(temp1 == temp2 && i != j && temp1[0] != '\''){
                    r = r->select(i,j);
                }
            }
        }
    }
    //make sure there are no duplicate variables in varIndices
    //project using the positions of the variables in 'q'
    //std::vector<int> varIndicesVec;
    //std::copy(varIndices.begin(), varIndices.end(), std::back_inserter(varIndicesVec));
    r = r->project(varIndices);
    //rename to match the names of the variables in 'q'
    r = r->rename(varNoRepeats);
    std::cout << queryName << "(";
    for(unsigned int i = 0; i < paramStrings.size(); i++){
        if(i == paramStrings.size()-1){
            std::cout << paramStrings[i] << ")? ";
        }
        else{
            std::cout << paramStrings[i] << ",";
        }
    }
    return r;
}

Relation* Interpreter::evaluatePredicate(Predicate& q) {
    std::string queryName = q.getID();
    //std::string queryName = q[i]->getID();
    std::map<std::string, Relation*> ImTheMap = db.getMap();
    Relation* r = ImTheMap[queryName];
    std::vector<Parameter*> param = q.getParameters();
    std::vector<std::string> paramStrings;
    //select for each constant in query 'q'
    std::vector<std::string> constants;
    std::vector<std::string> variables;
    std::vector<std::string> varNoRepeats;
    std::vector<int> constIndices;
    std::vector<int> varIndices;
    //std::set<Tuple> newTuples;
    for(unsigned int i = 0; i < param.size(); i++){
        std::string temp = param[i]->parameterToSting();
        paramStrings.push_back(temp);
        bool repeat = false;
        if(temp[0] == '\''){
            //std::cout << "this is temp[0] " << temp[0] << " !!!!!" << std::endl;
            constants.push_back(temp);
            constIndices.push_back(i);
        }
        else{
            variables.push_back(temp);
            for(unsigned int j = 0; j < varIndices.size(); j++){
                if(temp == variables[j] && j != i){
                    repeat = true;
                }
            }
            if(!repeat) {
                varIndices.push_back(i);
                varNoRepeats.push_back(temp);
            }
        }
    }
    for(unsigned int i = 0; i < constants.size(); i++){
        //std::cout << "this is the index: " << constIndices[i] << std::endl;
        //std::cout << "this is the constant: " << constants[i] << std::endl;
        r = r->select(constIndices[i],constants[i]);
    }
    //select for each pair of matching variables in 'q'
    if(variables.size() > 1) {
        for (unsigned int i = 0; i < paramStrings.size(); i++) {
            for (unsigned int j = 0; j < paramStrings.size(); j++){
                std::string temp1 = paramStrings[i];
                std::string temp2 = paramStrings[j];
                if(temp1 == temp2 && i != j && temp1[0] != '\''){
                    r = r->select(i,j);
                }
            }
        }
    }
    //make sure there are no duplicate variables in varIndices
    //project using the positions of the variables in 'q'
    //std::vector<int> varIndicesVec;
    //std::copy(varIndices.begin(), varIndices.end(), std::back_inserter(varIndicesVec));
    r = r->project(varIndices);
    //rename to match the names of the variables in 'q'
    r = r->rename(varNoRepeats);
    return r;
}







/*
std::cout << "this is a test" << std::endl;
for(int i = 0; i < q.size(); i++){
    std::string queryName = q[i]->getID();
    std::vector<Parameter*> queryParam = q[i]->getParameters();
    std::vector<std::string> queryAttribute;
    for(int j = 0; j < queryParam.size(); j++){
        queryAttribute.push_back(queryParam[j]->parameterToSting());
    }
    std::cout << queryName << "(";
    for(int k = 0; k < queryAttribute.size(); k++){
        std::cout <<queryAttribute[k] << ", ";
    }
    std::cout << ")" << std::endl;
}
*/
/*
for(int i = 0; i < f.size(); i++){
    std::string name = f[i]->getID();
    std::vector<Parameter*> param = f[i]->getParameters();
    std::vector<std::string> attributes;
    //std::set<Tuple> newTuples;
    for(int j = 0; j < param.size(); j++){
        attributes[j] = param[j]->parameterToSting();
    }
    Tuple newTuple = Tuple(attributes);
    for(int k = 0; k < relationVector.size(); i++){
        if(relationVector[i]->getName() == name){
            relationVector[i]->addTuple(newTuple);
        }
    }
}
 */