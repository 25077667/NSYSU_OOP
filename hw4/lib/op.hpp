#ifndef __OP_HPP__
#define __OP_HPP__
#include "token.hpp"

class Operator : public Token
{
public:
    Operator(string_view _token) : Token(_token, Tag::OP) {}
    Operator(string_view _token, Tag _tag) : Token(_token, _tag) {}
    Operator(const Token &_token) : Token(move(_token)) {}
};

#endif