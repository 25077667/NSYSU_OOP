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
constexpr frozen::map<string_view, Token, 25> tagTable{
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
    {string_view("break"), Token(string_view("break"), Tag::BREAK)},
    {string_view("do"), Token(string_view("do"), Tag::DO)},
    {string_view("else"), Token(string_view("else"), Tag::ELSE)},
    {string_view("true"), Token(string_view("true"), Tag::TRUE)},
    {string_view("false"), Token(string_view("false"), Tag::FALSE)},
    {string_view("while"), Token(string_view("while"), Tag::WHILE)},
    {string_view("temp"), Token(string_view("temp"), Tag::TEMP)},
    {string_view("-"), Token(string_view("-"), Tag::MINUS)},
    {string_view("index"), Token(string_view("index"), Tag::INDEX)},
};

#endif