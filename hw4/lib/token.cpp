#include "token.hpp"
#include <iostream>
#include "tag.hpp"
#include "word.hpp"
using namespace std;

ostream &operator<<(ostream &_out, const Token &_token)
{
    // the string_view will change after "READ", but don;t know why.
    string lexer(_token.token);
    _out << "Token: " << lexer << "\t(" << getWord(lexer, _token.tag) << ")";
    return _out;
}