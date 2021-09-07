#include "num.hpp"
#include "magic_enum.hpp"

std::string Num::to_string() const
{
    std::string str("Token: _\t(_)");
    str.replace(str.begin() + 7, str.begin() + 8, value);
    str.replace(str.begin() + 10, str.begin() + 11,
                magic_enum::enum_name(static_cast<Tag>(tag)));
    return str;
}