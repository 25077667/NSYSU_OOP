#include "token.hpp"

std::string Token::to_string() const
{
    std::string str("Token: _\t(_)");
    str.replace(str.begin() + 7, str.begin() + 8, {(char) tag});
    str.replace(str.begin() + 10, str.begin() + 11, {(char) tag});
    return str;
}