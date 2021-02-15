#include "type.hpp"
#include <algorithm>
#include <string_view>
#include <utility>
using namespace std;

Type::Type(string_view _type) : Token(_type, Tag::TYPE)
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

Type::Type(string_view _type, Tag _tag) : Type(_type)
{
    if (!*this)
        return;
    else if (__type == "BASIC")
        tag_mutator(Tag::BASIC);
    else if (__type == "SPECIFIER")
        tag_mutator(Tag::SPECIFIER);
}