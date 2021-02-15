#ifndef __NUM_HPP__
#define __NUM_HPP__
#include "token.hpp"

class Num : public Token
{
public:
    Num(string_view _token) : Token(_token, Tag::NUM) {}
};

#endif