#ifndef LEXER_HPP
#define LEXER_HPP
#include "token.hpp"
using namespace std;

class Lexer : public Token
{
public:
    Lexer() = default;
    Token scan();
};

#endif