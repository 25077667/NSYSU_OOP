#ifndef TYPE_HPP
#define TYPE_HPP
#include <array>
#include <string_view>
#include "token.hpp"

using namespace std;

class Token;

class Type : public Token
{
private:
    string_view __type;
    static constexpr array<string_view, 9> basic = {
        {"int", "float", "double", "char", "bool", "void", "string", "auto",
         "enum"}};  // class is not a type
    static constexpr array<string_view, 17> specifier = {
        {"signed", "unsigned", "long", "short", "static", "extern", "const",
         "inline", "volatile", "restrict", "public", "private", "protected",
         "virtual", "constexpr", "explicit", "friend"}};

public:
    Type() = delete;
    Type(string_view _type);
    Type(string_view _type, Tag _tag);
    ~Type() = default;
    string_view getType() { return this->__type; }
    operator bool() const { return __type == "BASIC" || __type == "SPECIFIER"; }
};

#endif