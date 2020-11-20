#ifndef LEXER_HPP
#define LEXER_HPP
#include "token.hpp"
using namespace std;

class Lexer
{
public:
    Lexer() = default;
    Token scan();
};

#endif