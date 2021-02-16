#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include "../lib/lexer.hpp"
#include "../lib/token.hpp"

int main()
{
    std::stringstream ss;
    std::streambuf *sb = std::cerr.rdbuf(ss.rdbuf());  // Save cerr to sb
    Lexer lex(cin);
    try {
        lex.scan();  // Throw exception on EOF
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    for_each(lex.begin(), next(lex.begin(), lex.size()),
             [](const std::unique_ptr<Token> &s) { cout << *s << endl; });
    std::cout << ss.str() << std::endl;
    std::cerr.rdbuf(sb);  // Restore cerr
    return 0;
}