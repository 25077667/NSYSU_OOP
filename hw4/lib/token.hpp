#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include <string_view>
#include "frozen/map.h"
#include "tag.hpp"
#include "type.hpp"
#include "word.hpp"
using namespace std;

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


// The second char must offset +1, because the peek offset +1
constexpr frozen::map<string_view, Token, 16> tagTable{
    {string_view("&'"), Token(string_view("&&"), Tag::AND)},
    {string_view("&"), Token(string_view("&"))},
    {string_view("|}"), Token(string_view("||"), Tag::OR)},
    {string_view("|"), Token(string_view("|"))},
    {string_view("=>"), Token(string_view("=="), Tag::EQ)},
    {string_view("="), Token(string_view("="))},
    {string_view("!>"), Token(string_view("!="), Tag::NE)},
    {string_view("!"), Token(string_view("!"))},
    {string_view("<>"), Token(string_view("<="), Tag::LE)},
    {string_view("<"), Token(string_view("<"))},
    {string_view("<?"), Token(string_view("<<"))},
    {string_view(">>"), Token(string_view(">="), Tag::GE)},
    {string_view(">"), Token(string_view(">"))},
    {string_view(">?"), Token(string_view(">>"))},
    {string_view(":"), Token(string_view(":"))},
    {string_view(":;"), Token(string_view("::"), Tag::SCOPE)},
};

#endif