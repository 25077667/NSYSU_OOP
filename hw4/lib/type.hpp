#ifndef TYPE_HPP
#define TYPE_HPP
#include <memory>
#include <string_view>
#include <unordered_map>
#include "tag.hpp"
#include "word.hpp"


class Type : public Word
{
private:
    const char width;

public:
    Type() = delete;
    Type(std::string_view _type, unsigned char _width)
        : Word(_type, Tag::BASIC), width(_width)
    {
    }
    Type(const Type &) = default;
    bool is_numeric() const
    {
        return lexeme == "char" || lexeme == "int" || lexeme == "float";
    }
    friend Type max(const Type &t1, const Type &t2);
};


const std::unordered_map<std::string_view, std::shared_ptr<Type>> type_table{
    {"int", std::make_shared<Type>("int", 4)},
    {"char", std::make_shared<Type>("char", 1)},
    {"bool", std::make_shared<Type>("bool", 1)},
    {"float", std::make_shared<Type>("float", 8)},
};

#endif