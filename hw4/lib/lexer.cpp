#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include <regex>
#include <stdexcept>
#include "tag.hpp"
#include "token.hpp"
using namespace std;

static const map<string, string> rePattern = {
    {string("HEX"), string("^0[xX][0-9A-Fa-f]+$")},
    {string("BIN"), string("^0[bB][0-9A-Fa-f]+$")},
    {string("NUM"), string("^[0-9]+(([uU]?[lL]?)|([lL]?[uU]?))$")},
    {string("FLOAT"), string("^([0-9]+(\\.[0-9]*)?|\\.[0-9]+)[fFlL]?$")},
    {string("MEMBER"), string("^\\.[a-zA-Z][0-9a-zA-Z]+$")},
};

static const char getChar()
{
    char in;
    while (isspace(cin.peek()))
        cin.ignore();  // skip white spaces
    if (cin.eof())
        throw runtime_error("End of file reached");
    cin.read(&in, 1);
    return in;
}

// prefix [+-]? is an operator, not in the number
static inline bool is_hex_notation(string const &s)
{
    return regex_match(s.c_str(), regex(rePattern.at("HEX")));
}

static inline bool is_bin_notation(string const &s)
{
    return regex_match(s.c_str(), regex(rePattern.at("BIN")));
}

static inline bool is_number(string const &s)
{
    return regex_match(s.c_str(), regex(rePattern.at("NUM")));
}

static inline bool is_float(string const &s)
{
    return regex_match(s.c_str(), regex(rePattern.at("FLOAT")));
}

static inline bool is_member(string const &s)
{
    return regex_match(s.c_str(), regex(rePattern.at("MEMBER")));
}

Token Lexer::scan()
{
    if (!cin.eof()) {
        // EOF +1 = '\0'; so if next char is EOF, we can append a '\0' at the
        // end of string. And the other word mapping
        // cannot combine this 2 into `make_pair` but don;t know why
        pair<char, char> biBytes;
        biBytes.first = getChar();
        biBytes.second = cin.peek() + 1;
        const auto inTagTable =
            make_pair(tagTable.find(string(1, biBytes.first)),
                      tagTable.find(string(1, biBytes.first) +
                                    string(1, biBytes.second)));
        // found in tagTable
        {
            // Match two char first
            if (inTagTable.second != tagTable.end()) {
                cin.ignore();  // ignore a byte(which peeked)
                return inTagTable.second->second;
            } else if (inTagTable.first != tagTable.end()) {
                cin.ignore();  // ignore a byte(which peeked)
                return inTagTable.first->second;
            }
        }
        if (isdigit(biBytes.first) || biBytes.first == '.') {
            string s;
            cin.putback(biBytes.first);

            char tmp;
            while (cin.read(&tmp, 1) && isdigit(tmp)) {
                s.push_back(tmp);
            }
            cin.putback(tmp);

            if (is_number(s) || is_hex_notation(s) || is_float(s) ||
                is_bin_notation(s))
                return Token(string_view(s), Tag::NUM);
            else if (is_member(s)) {  //.data
                reverse(s.begin(), s.end());
                s.pop_back();
                while (!s.empty()) {
                    cin.putback(s.back());
                    s.pop_back();
                }
                return Token(string_view("."), Tag::MEMBER);
            } else
                return Token(string_view(s), Tag::INVALID);
        }
        if (isalnum(biBytes.first)) {  // Only comes alphabate in head
            string s = string(1, biBytes.first);
            char tmp;
            while (cin.read(&tmp, 1) && isalnum(tmp)) {
                s.push_back(tmp);
            }
            cin.putback(tmp);

            auto isWordTag = tagTable.find(s);
            if (isWordTag != tagTable.end())
                return isWordTag->second;
            else if (!s.empty())
                return Token(string_view(s), Tag::ID);
        }
        return Token(string(1, biBytes.first));

    } else {
        throw runtime_error("End of file reached");
    }
}
