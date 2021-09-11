#ifndef TAG_HPP
#define TAG_HPP
#include <array>
#include <string_view>

enum class Tag : short {
    AND = 256,
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
    LSHIFT,
    RSHIFT,
    INVALID
};

namespace
{
constexpr std::array<std::string_view, 23> tag_lit = {
    "AND",  "BASIC", "BREAK", "DO",    "ELSE",   "EQ",     "FALSE",   "GE",
    "ID",   "IF",    "INDEX", "LE",    "MINUS",  "NE",     "NUM",     "OR",
    "REAL", "TEMP",  "TRUE",  "WHILE", "LSHIFT", "RSHIFT", "INVALID",
};
}

constexpr std::string_view get_teg_literal(Tag t)
{
    return tag_lit[static_cast<short>(t) - static_cast<short>(Tag::AND)];
}

#endif