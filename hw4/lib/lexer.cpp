#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>
#include "num.hpp"
#include "op.hpp"
#include "tag.hpp"
#include "token.hpp"
#include "type.hpp"
using namespace std;

static const char getChar(istream *is_ptr)
{
    char in;
    while (isspace(is_ptr->peek()))
        is_ptr->ignore();  // skip white spaces
    if (is_ptr->eof())
        throw runtime_error("End of file reached");
    is_ptr->read(&in, 1);
    return in;
}

// prefix [+-]? is an operator, not a number
static inline bool is_number(const string_view &s)
{
    return regex_match(s.data(), regex("^[0-9]+(([uU]?[lL]?)|([lL]?[uU]?))$"));
}

static inline bool is_float(const string_view &s)
{
    return regex_match(s.data(),
                       regex("^([0-9]+(\\.[0-9]*)?|\\.[0-9]+)[fFlL]?$"));
}

static string_view tok_getter(istream *is_ptr, char forward_peek)
{
    char head = is_ptr->peek();

    if (!(isalnum(head) || (head == '.' && isalpha(forward_peek)) ||
          head == '_')) {
        is_ptr->read(&head, 1);
        return string_view(&head);  // Is a single-character operator
    }

    auto is_match = (isalpha(head))
                        ? ([](int c) { return bool(isalnum(c) || c == '_'); })
                        : ([](int c) { return bool(isdigit(c) || c == '.'); });

    string s;
    do {
        s.push_back(head);
        is_ptr->read(&head, 1);  // read the peeked char
        head = is_ptr->peek();
    } while (is_match(head));
    return string_view(s.c_str());
}

static unique_ptr<Token> tok_mux(const string_view &tok)
{
    if (is_number(tok) || is_float(tok))
        return make_unique<Num>(tok);  // Number
    else if (Type(tok))
        return make_unique<Type>(tok, Tag::TYPE);  // Type
    else if (isalpha(*tok.begin()))
        return make_unique<Token>(tok, Tag::ID);  // Variable
    else
        return make_unique<Operator>(tok, Tag::OP);  // Operator
}

void Lexer::scan()
{
    while (!is_ptr->eof()) {
        // EOF +1 = '\0'; so if next char is EOF, we can append a '\0' at the
        // end of string.
        // And the ctor of pair is backed-evaluated the arguments.
        const pair<char, char> biBytes(is_ptr->peek() + 1, getChar(is_ptr));
        const auto inTagTable =
            make_pair(tagTable.find(string_view(&biBytes.second)),
                      tagTable.find([biBytes]() {
                          char buf[3] = {biBytes.second, biBytes.first, 0};
                          return string_view(buf);
                      }()));

        // Found in tag table
        if (inTagTable.first != tagTable.end() ||
            inTagTable.second != tagTable.end()) {
            is_ptr->ignore();  // don't care the `&var` case
            v_tok.push_back(
                make_unique<Operator>((inTagTable.second != tagTable.end())
                                          ? inTagTable.second->second
                                          : inTagTable.first->second));
            continue;
        }
        is_ptr->putback(biBytes.second);
        auto tok = tok_getter(is_ptr, biBytes.first - 1);
        cout << string(tok) << endl;
        v_tok.push_back(tok_mux(tok));
    }
}