#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2a(const std::string& input);
    void S2b(const std::string& input);
    //void S3a(const std::string& input);
    void S3b(const std::string& input);

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // COMMENTAUTOMATON_H

