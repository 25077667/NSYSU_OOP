#ifndef TAG_HPP
#define TAG_HPP
#include <memory>
#include <string_view>
#include <unordered_map>

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

#endif