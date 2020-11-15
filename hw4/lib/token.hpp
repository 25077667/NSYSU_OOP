#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include <string_view>
#include "tag.hpp"
#include "type.hpp"
#include "word.hpp"

class Token
{
    std::string_view token;
    Tag tag = Tag::EMPTY;

public:
    Token() = default;
    constexpr explicit Token(std::string_view _token) : token(_token) {}
    constexpr explicit Token(std::string_view _token, Tag _tag)
        : token(_token), tag(_tag)
    {
    }
    friend std::ostream &operator<<(std::ostream &_out, const Token &_token);
    Token operator=(const Token &_token);
    operator bool() const { return !this->token.empty(); }
};

std::ostream &operator<<(std::ostream &_out, const Token &_token)
{
    _out << "Token: " << (_token.token) << "\t("
         << getWord(_token.token, _token.tag) << ")";
    return _out;
}
#endif