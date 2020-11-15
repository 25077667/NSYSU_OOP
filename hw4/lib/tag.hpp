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
    WHILE
};

constexpr frozen::map<std::string, Token, 16> tagTable{
    {"&&", Token("&&")}, {"&", Token("&")},   {"||", Token("||")},
    {"|", Token("|")},   {"==", Token("==")}, {"=", Token("=")},
    {"!=", Token("!=")}, {"!", Token("!")},   {"<=", Token("<=")},
    {"<", Token("<")},   {"<<", Token("<<")}, {">=", Token(">=")},
    {">", Token(">")},   {">>", Token(">>")}, {":", Token(":")},
    {"::", Token("::")},
};

#endif