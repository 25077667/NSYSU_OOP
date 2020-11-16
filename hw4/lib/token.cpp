#include "token.hpp"
#include <iostream>
#include "tag.hpp"
#include "word.hpp"
using namespace std;

ostream &operator<<(ostream &_out, const Token &_token)
{
    _out << "Token: " << (_token.token) << "\t("
         << getWord(_token.token, _token.tag) << ")";
    return _out;
}