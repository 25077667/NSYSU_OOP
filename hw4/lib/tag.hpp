#ifndef TAG_HPP
#define TAG_HPP
#include <map>
#include "frozen/map.h"
#include "token.hpp"

enum class Tag : char {
    EMPTY,
    AND,
    BASIC,
    BREAK,
    DO,
    ELSE,
    EQ,
    FALSE,
    GE,
    ID,
    IF,
    INDEX,
    LE,
    MINUS,
    NE,
    NUM,
    OR,
    REAL,
    TEMP,
    TRUE,
    WHILE,
    SCOPE,
};

bool operator!(Tag tag)
{
    return tag == static_cast<Tag>(0);
}

// The second char must offset +1, because the peek offset +1
constexpr frozen::map<std::string_view, Token, 16> tagTable{
    {"&'", Token("&&", Tag::AND)},
    {"&", Token("&")},
    {"|}", Token("||", Tag::OR)},
    {"|", Token("|")},
    {"=>", Token("==", Tag::EQ)},
    {"=", Token("=")},
    {"!>", Token("!=", Tag::NE)},
    {"!", Token("!")},
    {"<>", Token("<=", Tag::LE)},
    {"<", Token("<")},
    {"<?", Token("<<")},
    {">>", Token(">="), Tag::GE},
    {">", Token(">")},
    {">?", Token(">>")},
    {":", Token(":")},
    {":;", Token("::"), Tag::SCOPE},
};

#endif