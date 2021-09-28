#ifndef UNDEFINEDCOMMENTAUTOMATON_H
#define UNDEFINEDCOMMENTAUTOMATON_H

#include "Automaton.h"

class UndefinedCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

public:
    UndefinedCommentAutomaton() : Automaton(TokenType::UNDEFINEDCOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // UNDEFINEDCOMMENTAUTOMATON_H

