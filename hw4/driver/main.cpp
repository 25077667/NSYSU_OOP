#include <iostream>
#include "../lib/lexer.hpp"
#include "../lib/token.hpp"

int main()
{
    try {
        Lexer lexer;
        Token t;
        while (t = lexer.scan())
            std::cout << t << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    return 0;
}