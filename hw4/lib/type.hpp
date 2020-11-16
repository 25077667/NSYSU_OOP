#ifndef TYPE_HPP
#define TYPE_HPP
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

class Type
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
    ~Type() = default;
    string_view getType() { return this->__type; }
    operator bool() const { return __type == "BASIC" || __type == "SPECIFIER"; }
};

Type::Type(string_view _type)
{
    auto mux = make_pair(find(basic.begin(), basic.end(), _type),
                         find(specifier.begin(), specifier.end(), _type));
    if (mux.first != basic.end())
        this->__type = "BASIC";
    else if (mux.second != specifier.end())
        this->__type = "SPECIFIER";
    else
        this->__type = _type;
}

#endif