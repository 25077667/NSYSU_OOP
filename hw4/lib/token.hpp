#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include <string_view>
#include "frozen/map.h"
#include "tag.hpp"
#include "type.hpp"
#include "word.hpp"
using namespace std;

extern string getWord(string_view lexeme, Tag tag);

class Token
{
    string_view token;
    Tag tag = Tag::EMPTY;

public:
    Token() = default;
    constexpr Token(string_view _token) : token(_token) {}
    constexpr Token(string_view _token, Tag _tag) : token(_token), tag(_tag) {}
    friend ostream &operator<<(ostream &_out, const Token &_token);
    constexpr Token operator=(const Token &_token)
    {
        this->token = _token.token;
        this->tag = _token.tag;
        return *this;
    }
    operator bool() const { return !this->token.empty(); }
};

ostream &operator<<(ostream &_out, const Token &_token)
{
    _out << "Token: " << (_token.token) << "\t("
         << getWord(_token.token, _token.tag) << ")";
    return _out;
}

// The second char must offset +1, because the peek offset +1
constexpr frozen::map<std::string_view, Token, 16> tagTable{
    {std::string_view("&'"), Token(std::string_view("&&"), Tag::AND)},
    {std::string_view("&"), Token(std::string_view("&"))},
    {std::string_view("|}"), Token(std::string_view("||"), Tag::OR)},
    {std::string_view("|"), Token(std::string_view("|"))},
    {std::string_view("=>"), Token(std::string_view("=="), Tag::EQ)},
    {std::string_view("="), Token(std::string_view("="))},
    {std::string_view("!>"), Token(std::string_view("!="), Tag::NE)},
    {std::string_view("!"), Token(std::string_view("!"))},
    {std::string_view("<>"), Token(std::string_view("<="), Tag::LE)},
    {std::string_view("<"), Token(std::string_view("<"))},
    {std::string_view("<?"), Token(std::string_view("<<"))},
    {std::string_view(">>"), Token(std::string_view(">="), Tag::GE)},
    {std::string_view(">"), Token(std::string_view(">"))},
    {std::string_view(">?"), Token(std::string_view(">>"))},
    {std::string_view(":"), Token(std::string_view(":"))},
    {std::string_view(":;"), Token(std::string_view("::"), Tag::SCOPE)},
};

#endif