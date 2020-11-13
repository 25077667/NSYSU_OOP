#ifndef TYPE_HPP
#define TYPE_HPP
#include <array>
#include <iostream>

using namespace std;

class Type
{
private:
    string __type;
    static array<string, 9> allType = {"int",  "float", "double", "char",
                                       "bool", "void",  "string", "auto",
                                       "enum"};  // class is not a type
    static array<string, 14> specifier = {
        "signed", "unsigned", "long",      "short",    "static",
        "extern", "const",    "inline",    "volatile", "restrict",
        "public", "private",  "protected", "virtual"};

public:
    Type() = default;
    Type(string _type);
    ~Type() = default;
    string getType();
};

Type::Type(string _type) : __type(_type) {}

#endif