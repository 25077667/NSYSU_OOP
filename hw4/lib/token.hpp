#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include "type.hpp"
#include "word.hpp"

using namespace std;

class Token
{
    std::string token;

public:
    Token() = default;
    Token(string _token) : token(_token) {}
    friend ostream &operator<<(ostream &_out, const Token &_token);
    Token operator=(const Token &_token);
};

ostream &operator<<(ostream &_out, const Token &_token)
{
    _out << "Token: " << (_token.token) << "\t(" << getWord(_token.token)
         << ")";
    return _out;
}
#endif