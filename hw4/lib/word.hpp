#ifndef WORD_HPP
#define WORD_HPP
#include "tag.hpp"
#include "token.hpp"

enum class Tag : short;
class Token;

class Word : public Token
{
protected:
    const std::string lexeme;

public:
    Word() = delete;
    Word(std::string_view _token, Tag _tag)
        : lexeme(_token), Token(static_cast<short>(_tag))
    {
    }
    Word(const char *_token, Tag _tag) : Word(std::string_view(_token), _tag) {}
    std::string to_string() const override;
};

#endif