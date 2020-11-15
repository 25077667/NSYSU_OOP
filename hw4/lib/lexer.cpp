#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include "tag.hpp"
#include "token.hpp"

using namespace std;

static const char getChar()
{
    char in;
    while (cin.read(&in, 1) && isspace(in))
        ;  // skip white spaces
    return in;
}

Token Lexer::scan()
{
    if (!cin.eof()) {
        pair<char, char> biBytes = make_pair(getChar(), cin.peek() + 1);
        const auto isFound =
            make_pair(tagTable.find(string(1, biBytes.first)),
                      tagTable.find(string(1, biBytes.first) +
                                    string(1, biBytes.second)));
        if (isFound.first ^ isFound.second)  // found in tagTable
        {
            cin.ignore();  // ignore a byte(which peeked)
            return *(frozen::map<std::string, Token, 16>::iterator(
                isFound.first ^ isFound.second ^ tagTable.end()));
        }
        while (isdigit(biBytes.first)) {
            ;  // TODO: return immediately
        }
        while (isalnum(biBytes.first)) {
            ;
        }
        return Token(string(1, biBytes.first));

    } else {
        throw "End of file reached";
    }
}