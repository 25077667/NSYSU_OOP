#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include "type.hpp"
#include "word.hpp"

class Token
{
    std::string token;

public:
    Token() = default;
    constexpr explicit Token(std::string _token) : token(_token) {}
    friend std::ostream &operator<<(std::ostream &_out, const Token &_token);
    Token operator=(const Token &_token);
};

std::ostream &operator<<(std::ostream &_out, const Token &_token)
{
    _out << "Token: " << (_token.token) << "\t(" << getWord(_token.token)
         << ")";
    return _out;
}
#endif