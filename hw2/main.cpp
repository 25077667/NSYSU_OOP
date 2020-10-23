#include <iostream>
#include "argParser.hpp"
#include "tar.hpp"

int main(int argc, char *argv[])
{
    char mode = parser(argc, argv);
    Tar myTar(std::string(argv[2]), mode);
    for (int i = 3; i <= argc; i++) {
        try {
            myTar.operate(std::string(argv[i]));
        } catch (char const *error) {
            std::cerr << error << std::endl;
        }
    }
    return 0;
}