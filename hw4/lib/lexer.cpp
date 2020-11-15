#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include "tag.hpp"
#include "token.hpp"

using namespace std;

static const char getChar(istream &in)
{
    char in;
    while (cursor.read(&in, 1) && isspace(in))
        ;  // skip white spaces
    return in;
}

Token Lexer::scan()
{
    if (!this->cursor.eof()) {
        pair<char, char> biBytes =
            make_pair(getChar(this->cursor), this->cursor.peek());
        const auto isFound = make_pair(
            tagTable.find(string(biBytes.first)),
            tagTable.find(string(biBytes.first) + string(biBytes.second)));
        // if (isFound)  // found
        return isFound->second();

    } else {
        throw "End of file reached";
    }
}