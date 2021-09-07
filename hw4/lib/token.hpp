#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <memory>
#include <string_view>
#include <unordered_map>
#include "tag.hpp"

class Token
{
protected:
    const short tag;

public:
    Token() = delete;
    Token(const Token &) = delete;
    Token(Token &&) = default;
    Token &operator=(const Token &) = delete;
    Token &operator=(Token &&) = delete;
    explicit Token(short _tag) : tag(_tag) {}
    operator bool() const { return this->tag; }
    virtual std::string to_string() const;
};

#endif