#ifndef LEXER_HPP
#define LEXER_HPP
#include <memory>
#include "token.hpp"

class Lexer
{
public:
    constexpr Lexer() = default;
    std::shared_ptr<Token> scan();
};

#endif