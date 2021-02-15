#include "token.hpp"
#include <iostream>
#include "magic_enum.hpp"
#include "tag.hpp"
using namespace std;

ostream &operator<<(ostream &_out, const Token &_token)
{
    string_view tag(magic_enum::enum_name(_token.tag));
    if (_token.tag == Tag::OP)
        tag = _token.token;
    _out << "Token: " << _token.token << "\t(" << tag << ")";
    return _out;
}