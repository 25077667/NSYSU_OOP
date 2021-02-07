#include <iostream>
#include "../lib/lexer.hpp"
#include "../lib/token.hpp"

int main()
{
    try {
        Lexer lex(cin);
        for_each(lex.begin(), next(lex.begin(), lex.size()),
                 [](Token s) { cout << s << endl; });
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    return 0;
}