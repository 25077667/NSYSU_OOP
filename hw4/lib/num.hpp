#ifndef NUM_HPP
#define NUM_HPP

#include <string_view>
#include "token.hpp"

class Num : public Token
{
    const std::string value;

public:
    Num() = delete;
    Num(std::string_view s) : value(s), Token(static_cast<short>(Tag::NUM)) {}
    Num(std::string_view s, Tag t) : value(s), Token(static_cast<short>(t)) {}
    std::string to_string() const override;
};

#endif