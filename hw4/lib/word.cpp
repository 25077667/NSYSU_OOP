#include "word.hpp"


std::string Word::to_string() const
{
    std::string str("Token: _\t(_)");
    str.replace(str.begin() + 7, str.begin() + 8, lexeme);
    str.replace(str.begin() + 10, str.begin() + 11,
                get_teg_literal(static_cast<Tag>(tag)));
    return str;
}