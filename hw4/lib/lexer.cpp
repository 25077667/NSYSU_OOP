#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include "num.hpp"
#include "tag.hpp"
#include "token.hpp"
#include "type.hpp"

namespace
{
const std::unordered_map<std::string_view, std::shared_ptr<Word>> tag_table{
    {"&&", std::make_shared<Word>("&&", Tag::AND)},
    {"||", std::make_shared<Word>("||", Tag::OR)},
    {"==", std::make_shared<Word>("==", Tag::EQ)},
    {"!=", std::make_shared<Word>("!=", Tag::NE)},
    {"<=", std::make_shared<Word>("<=", Tag::LE)},
    {">=", std::make_shared<Word>(">=", Tag::GE)},
    {"<<", std::make_shared<Word>(">=", Tag::LSHIFT)},
    {">>", std::make_shared<Word>(">=", Tag::RSHIFT)},
    {"break", std::make_shared<Word>("break", Tag::BREAK)},
    {"do", std::make_shared<Word>("do", Tag::DO)},
    {"else", std::make_shared<Word>("else", Tag::ELSE)},
    {"true", std::make_shared<Word>("true", Tag::TRUE)},
    {"false", std::make_shared<Word>("false", Tag::FALSE)},
    {"while", std::make_shared<Word>("while", Tag::WHILE)},
    {"if", std::make_shared<Word>("if", Tag::IF)},
};

char fetch_byte(std::istream &_is, bool ignore_space = false)
{
    char in;
    if (ignore_space)
        while (isspace(_is.peek()))
            _is.ignore();  // skip white spaces
    if (_is.eof())
        throw std::runtime_error("End of file reached");
    _is.read(&in, 1);
    return in;
}

std::shared_ptr<Token> make_tok(char c)
{
    const std::string str(std::array<char, 3>{c, c, 0}.data());
    return tag_table.find(str)->second;
}

std::shared_ptr<Token> make_tok(char c1, char c2)
{
    const std::string str(std::array<char, 3>{c1, c2, 0}.data());
    return tag_table.find(str)->second;
}

auto tok_mux(std::istream &_is, char c)
{
    if (_is.peek() == c)
        return make_tok(c);
    else if ((c == '>' || c == '<') && _is.peek() == '=') {
        _is.ignore(1);  // it is '='
        return make_tok(c, '=');
    } else
        return std::make_shared<Token>(static_cast<short>(c));
}

std::shared_ptr<Num> num_tok(std::istream &_is, char byte)
{
    std::string num;
    char peek = byte;
    do {
        peek = fetch_byte(_is);
        num.push_back(peek);
    } while (peek);

    if (peek != '.')  // Not a floating point
        return std::make_shared<Num>(num);

    // It is a floating point
    // Don't care the 'f' or 'e'
    while (true) {
        peek = fetch_byte(_is);
        if (!::isdigit(peek))
            break;
        num.push_back(peek);
    }

    return std::make_shared<Num>(num, Tag::REAL);
}

std::shared_ptr<Token> alpha_tok(std::istream &is, char byte)
{
    std::string str;
    char peek = byte;
    do {
        peek = fetch_byte(is);
        str.push_back(peek);
    } while (::isalnum(peek));

    const auto tag_is_find = tag_table.find(str);
    if (tag_is_find != tag_table.end())
        return tag_is_find->second;

    const auto type_is_find = type_table.find(str);
    if (type_is_find != type_table.end())
        return type_is_find->second;

    return std::make_shared<Word>(str, Tag::ID);
}

}  // namespace

std::shared_ptr<Token> Lexer::scan()
{
    std::istream &is = std::cin;
    const char byte = fetch_byte(is, true);

    auto is_in_ops = [](const char byte) -> bool {
        constexpr std::array<char, 6> ops = {'&', '|', '=', '!', '<', '>'};
        return std::find(ops.begin(), ops.end(), byte) != ops.end();
    };

    if (is_in_ops(byte))
        return tok_mux(is, byte);

    if (::isdigit(byte))
        return num_tok(is, byte);

    if (::isalpha(byte))
        return alpha_tok(is, byte);

    return std::make_shared<Token>(byte);
}
