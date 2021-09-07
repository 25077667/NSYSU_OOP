#include <iostream>
#include "../lib/lexer.hpp"
#include "../lib/token.hpp"

int main()
{
    try {
        Lexer lexer;
        while (auto t = lexer.scan())
            std::cout << t->to_string() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    return 0;
}