#include <iostream>
#include "argParser.hpp"
#include "tar.hpp"

int main(int argc, char *argv[])
{
    char mode = parser(argc, argv);
    try {
        Tar myTar(std::string(argv[2]), mode);
        for (int i = 3; i < argc; i++) {
            myTar.operate(std::string(argv[i]));
        }
        if (mode & 0b00010000)
            myTar.operate(std::string());
    } catch (char const *error) {
        std::cerr << error << std::endl;
    }
    return 0;
}