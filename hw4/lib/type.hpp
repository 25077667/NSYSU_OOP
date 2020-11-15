#ifndef TYPE_HPP
#define TYPE_HPP
#include <array>
#include <iostream>

using namespace std;

class Type
{
private:
    string_view __type;
    static constexpr array<string_view, 9> allType = {
        {"int", "float", "double", "char", "bool", "void", "string_view",
         "auto", "enum"}};  // class is not a type
    static constexpr array<string_view, 17> specifier = {
        {"signed", "unsigned", "long", "short", "static", "extern", "const",
         "inline", "volatile", "restrict", "public", "private", "protected",
         "virtual", "constexpr", "explicit", "friend"}};

public:
    Type() = default;
    Type(string_view _type);
    ~Type() = default;
    string_view getType();
};

Type::Type(string_view _type) : __type(_type) {}

#endif