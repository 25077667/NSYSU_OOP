#ifndef TAG_HPP
#define TAG_HPP
#include <string_view>

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
    MEMBER,
    INVALID
};

bool operator!(Tag tag)
{
    return tag == static_cast<Tag>(0);
}

#endif