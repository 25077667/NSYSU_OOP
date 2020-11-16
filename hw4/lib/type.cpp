#include "type.hpp"
#include <algorithm>
#include <array>
#include <string_view>
#include <utility>
using namespace std;

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