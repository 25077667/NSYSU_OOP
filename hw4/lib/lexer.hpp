#ifndef LEXER_HPP
#define LEXER_HPP
#include <iostream>
#include "token.hpp"
using namespace std;

class Lexer
{
    istream cursor;

public:
    Lexer() = default;
    Lexer(istream _in) : cursor(_in) {}
    Token scan();
};

Token Lexer::scan()
{
    if (!this->cursor.eof()) {
        // get something
    } else {
        throw "End of file reached"
    }
}

#endif