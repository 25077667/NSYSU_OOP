#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>
#include <memory>
#include <utility>
#include <vector>
#include "token.hpp"
using namespace std;

class Lexer
{
    istream *is_ptr;
    vector<unique_ptr<Token>> v_tok;

public:
    Lexer() = delete;
    Lexer(istream &_is) { is_ptr = &_is; }
    decltype(auto) begin() const { return v_tok.begin(); }
    decltype(auto) end() const { return v_tok.end(); }
    auto size() const { return v_tok.size(); }
    void scan();
};

#endif