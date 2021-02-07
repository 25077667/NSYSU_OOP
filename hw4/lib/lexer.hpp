#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>
#include <utility>
#include <vector>
#include "token.hpp"
using namespace std;

class Lexer : public istream
{
    istream is;
    vector<Token> v_tok;
    virtual void set_scan(std::istream &_is) { is = move(_is); }
    void scan();

public:
    Lexer() = delete;
    Lexer(istream &_is) { set_scan(_is); }
    decltype(auto) begin() const { return v_tok.begin(); }
    decltype(auto) end() const { return v_tok.end(); }
    auto size() const { return v_tok.size(); }
};

#endif