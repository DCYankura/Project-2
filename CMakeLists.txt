# cmake_minimum_required(VERSION <specify CMake version here>)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h CommaAutomaton.cpp CommaAutomaton.h PeriodAutomaton.cpp PeriodAutomaton.h QMarkAutomaton.cpp QMarkAutomaton.h LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h IDAutomaton.cpp IDAutomaton.h CommentAutomaton.cpp CommentAutomaton.h StringAutomaton.cpp StringAutomaton.h UndefinedStringAutomaton.cpp UndefinedStringAutomaton.h UndefinedCommentAutomaton.cpp UndefinedCommentAutomaton.h DatalogProgram.cpp DatalogProgram.h Rule.cpp Rule.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Parser.cpp Parser.h)
