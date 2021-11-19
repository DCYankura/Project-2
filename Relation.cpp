#include "Relation.h"
Relation::Relation(std::set<Tuple> tuples, std::string name, Header* headers) {
    this->tuples = tuples;
    this->name = name;
    this->headers = headers;
}
//TODO select, project, and rename need to return Relation objects
Relation* Relation::select(int index, std::string value){
//select rows in column index that equal value
    std::set<Tuple> newTuples;
    //std::vector<std::string> newHeaders;
    //std::vector<std::string> attributes = headers->getAttributes();
    std::set<Tuple>::iterator it;
    //int tupleSize = tuples.size();
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        if(tempValues[index] == value) {
            newTuples.insert(*it);
        }
    }
    Relation* newRelation = new Relation(newTuples, name, headers);
    return newRelation;
}

Relation* Relation::select(int column1, int column2) {
    //select rows for which values in column 1 = values in column 2
    std::set<Tuple> newTuples;
    //std::vector<std::string> newHeaders;
    //std::vector<std::string> attributes = headers->getAttributes();
    std::set<Tuple>::iterator it;
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        std::string test1 = tempValues[column1];
        std::string test2 = tempValues[column2];
        if(tempValues[column1] == tempValues[column2]) {
            newTuples.insert(*it);
        }
    }
    Relation* newRelation = new Relation(newTuples, name, headers);
    return newRelation;
}
Relation* Relation::project(std::vector<int> indices) {
    std::set<Tuple> newTuples;
    std::vector<std::string> newHeaders;
    std::vector<std::string> attributes = headers->getAttributes();
    //first for loop populates new header objects
    for(unsigned int i = 0; i < indices.size(); i++){
        //std::set<Tuple>::iterator it = tuples.begin();
        //std::advance(it,indices[i]);
        //newTuples.insert(*it);
        newHeaders.push_back(attributes[indices[i]]);
    }
    //second for loop iterates through set of tuples to create new set of tuples
    std::set<Tuple>::iterator it;
    for(it = tuples.begin(); it != tuples.end(); it++){
        Tuple tupleIter = *it;
        std::vector<std::string> tempValues = tupleIter.getValues();
        std::vector<std::string> newValues;
        for(unsigned int i = 0; i < indices.size(); i++){
            newValues.push_back(tempValues[indices[i]]);
        }
        Tuple tempTuple = Tuple(newValues);
        newTuples.insert(tempTuple);
    }
    Header* tempHeader = new Header(newHeaders);
    Relation* newRelation = new Relation(newTuples, name, tempHeader);
    return newRelation;
}
Relation* Relation::rename(std::vector<std::string> newAttributes) {
    Header* tempHeader = new Header(newAttributes);
    Relation* newRelation = new Relation(tuples, name, tempHeader);
    return newRelation;
}

Relation* Relation::join(Relation* relationToJoin) {
    // 1) Calculate which column pairs between the left relation and the right relation need to match values
    Header* header2 = relationToJoin->getHeaders();
    std::vector<std::string> attributesR1 = headers->getAttributes();
    std::vector<std::string> attributesR2 = header2->getAttributes();
    std::vector<int> indicesH1;
    std::vector<int> indicesH2;
    for(unsigned int i = 0; i < attributesR1.size(); i++){
        for(unsigned int j = 0; j < attributesR2.size(); j++){
            if(attributesR1[i] == attributesR2[j]){
                indicesH1.push_back(i);
                indicesH2.push_back(j);
            }
        }
    }

    // 2) Calculate which columns of the right relation do not have a match in the left relation, and therefore need to be copied (this step is probably best done at the same time as step 1, actually)

    // 3) Make a combined header by copying all of the left header, and the non-matching columns of the right relation (calculated in step 2)
    Header* newHeader = combineHeaders(headers,header2);
    // 4) Make a new relation with the combined header (it will start with no tuples in it)
    Relation* newRelation = new Relation();
    newRelation->setHeader(newHeader);
    // 5) Use a pair of nested for-loops to look at each possible pairing of a tuple from the left and a tuple from the right
    std::set<Tuple>::iterator it;
    std::set<Tuple>::iterator it2;
    std::set<Tuple> tuplesToJoin = relationToJoin->getTuples();
    for(it = tuples.begin(); it != tuples.end(); it++){
        for(it2 = tuplesToJoin.begin(); it2 != tuplesToJoin.end(); it2++){
            Tuple tuple1 = *it;
            Tuple tupleToCompare = *it2;
            bool canJoin = isJoinable(tuple1, tupleToCompare, indicesH1, indicesH2);
            if(canJoin){
                Tuple combinedTuple = combineTuple(tuple1, tupleToCompare, indicesH1, indicesH2);
                newRelation->addTuple(combinedTuple);
            }
        }
    }
    // 6) Make sure all column pairs that need to match between the two tuples (calculated in step 1) do have matching values. If they don't, then do nothing else with this pair of tuples (do not do step 7 or 8 for this pair).

    // 7) Assuming step 5 passes and they do match where needed, make a new combined tuple. This is done by copying all of the left tuple, and then copying the non-matching columns of the right tuple (calculated in step 2)

    // 8) Put the combined tuple into the new relation (the one made in step 4)

    // 9) Once all pairs of tuples have been checked, return the new relation
    return newRelation;
}

bool Relation::unionize(Relation* &dbRelation) {
    //Insert function gives back pair that tells if tuple was inserted or not
    //pass in database as parameter
    bool updated = false;
    std::set<Tuple>::iterator it;
    std::pair<std::set<Tuple>::iterator, bool> ret;
    //get relation from database that has the same name as relationToJoin
    //std::string nameToJoin = relation->getName();
    //std::map<std::string, Relation*> ImTheMap = db.getMap();
    //Relation* dbRelation = ImTheMap[name];
    //add tuples from relationToJoin into dbRelation and check to see if added
    //std::set<Tuple> tupleDB = dbRelation->getTuples();
    //std::set<Tuple> tuplesToJoin = relationToJoin->getTuples();
    for(it = tuples.begin(); it != tuples.end(); it++){
        ret = (dbRelation->getTuples()).insert(*it);
        if(ret.second){
            updated = true;
            //print out unique tuples here
            //std::set<Tuple> tupleSet = ruleRelation->getTuples();
            //std::set<Tuple>::iterator it;
            Header* ruleHeaders = dbRelation->getHeaders();
            std::vector<std::string> attributes = ruleHeaders->getAttributes();
            std::cout << '\t';
            Tuple tempTuple = *it;
            std::vector<std::string> tupleValues = tempTuple.getValues();
            for(unsigned int j = 0; j < attributes.size(); j++){
                if(j == attributes.size()-1) {
                    std::cout << attributes[j] << "=" << tupleValues[j] << std::endl;
                }
                else{
                    std::cout << attributes[j] << "=" << tupleValues[j] << ", ";
                }
            }
        }
    }
    return updated;
}

Header* Relation::combineHeaders(Header *header1, Header *header2) {
    std::vector<std::string> attributesH1 = header1->getAttributes();
    std::vector<std::string> attributesH2 = header2->getAttributes();
    std::vector<std::string> newAttributes = attributesH1;
    bool isRepeat;
    for(unsigned int i = 0; i < attributesH2.size(); i++){
        isRepeat = false;
        for(unsigned int j = 0; j < attributesH1.size(); j++){
            if(attributesH1[j] == attributesH2[i]){
                isRepeat = true;
            }
        }
        if(!isRepeat){
            newAttributes.push_back(attributesH2[i]);
        }
    }
    Header* newHeader = new Header(newAttributes);
    return newHeader;
}

bool Relation::isJoinable(Tuple tuple1, Tuple tuple2, std::vector<int> indicesT1, std::vector<int> indicesT2) {
    bool joinable = true;
    std::vector<std::string> valuesT1 = tuple1.getValues();
    std::vector<std::string> valuesT2 = tuple2.getValues();
    for(unsigned int i = 0; i <indicesT1.size(); i++){
        int indexT1 = indicesT1[i];
        int indexT2 = indicesT2[i];
        if(valuesT1[indexT1] != valuesT2[indexT2]){
            joinable = false;
        }
    }
    return joinable;
}

Tuple Relation::combineTuple(Tuple tuple1, Tuple tuple2, std::vector<int> indicesT1, std::vector<int> indicesT2) {
    std::vector<std::string> valuesT1 = tuple1.getValues();
    std::vector<std::string> valuesT2 = tuple2.getValues();
    std::vector<std::string> newValues = valuesT1;
    /*
    bool isMatch = false;
    for(int i = 0; valuesT2.size(); i++){
        isMatch = false;
        for(int j = 0; j < indicesT1.size(); j++){
            if(i == indicesT2[j]){
                isMatch = true;
            }
        }
        if(!isMatch){
            newValues.push_back(valuesT2[i]);
        }
    }
     */
    bool isMatch;
    for(unsigned int i = 0; i < valuesT2.size(); i++){
        isMatch = false;
        for(unsigned int j = 0; j < indicesT2.size(); j++){
            int temp = i;
            if(temp == indicesT2[j]){
                isMatch = true;
            }
        }
        if(!isMatch){
            newValues.push_back(valuesT2[i]);
        }
    }
    Tuple newTuple = Tuple(newValues);
    return newTuple;
}

void Relation::relationToString() {
    //std::cout << name << "(";
    std::vector<std::string> attributes = headers->getAttributes();
    /*
    for(int i = 0; i < attributes.size(); i++){
        if(i == attributes.size() - 1){
            std::cout << attributes[i] << ")? ";
        }
        else{
            std::cout << attributes[i] << ",";
        }
    }
    */
    if(tuples.size() == 0){
        std::cout << "No" << std::endl;
    }
    else{
        std::cout << "Yes(" << tuples.size() << ")" << std::endl;
        for(Tuple t : tuples){
            std::vector<std::string> values = t.getValues();
            if(values.size() != 0) {
                std::cout << " " << " ";
            }
            for(unsigned int j = 0; j < values.size(); j++) {
                if(j == values.size()- 1) {
                    std::cout << attributes[j] << "=" << values[j] << std::endl;
                }
                else{
                    std::cout << attributes[j] << "=" << values[j] << ", ";
                }
            }
        }
    }
}