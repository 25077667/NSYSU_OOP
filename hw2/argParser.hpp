#ifndef __ARG_PARSER_HPP__
#define __ARG_PARSER_HPP__
#include <algorithm>
#include <cstring>
#include <iostream>

#define IS_NEED_HELP(argc, argv)                                             \
    (((argc == 2) && (strncmp(argv[1], "help", max(strlen(argv[1]), 4)))) && \
     (argc != 3))

static int needHelp(std::string procName)
{
    std::cerr << "Usage: " << procName << " option(s) tarfile [sources]"
              << std::endl
              << "Usage: " << procName << " help\n"
              << std::endl;
    _Exit(-1);
}

static void help(std::string procName)
{
    std::cout
        << "Usage: " << procName
        << " options(s) tarfile [sources]\nUsage: " << procName << " help"
        << std::endl
        << std::endl
        << "Important:" << std::endl
        << "   This program is not meant to be a full tar implementation."
        << std::endl
        << "   Only a subset of the functions the GNU tar utility has "
        << "are supported." << std::endl
        << std::endl
        << "    Special files that already exist will not be replaced when "
        << "extracting (no error)" << std::endl
        << "   Regular expression expansion/matching is not done." << std::endl
        << std::endl "    options (only one allowed at a time):" << std::endl
        << "       a - append files to archive" << std::endl
        << "       c - create a new archive" << std::endl
        << std::endl
        << "       r - remove files from the directory" << std::endl
        << "       t - list the files in the directory" << std::endl
        << "       u - update entries that have newer modification times"
        << std::endl
        << "       x - extract from archive" << std::endl
        << std::endl "    other options:" << std::endl
        << "       v - make operation verbose" << std::endl
        << std::endl "Ex: " << procName << " vl archive.tar" << std::endl;
    _Exit(0);
}
/*
 * Mode format:
 * The bits:
 * |a|c|r|t|u|x|v|v|
 * 1 is on, 0 is off.
 * The vv bits are:
 *       0: no print;
 *       1: print file names;
 *       2: print file properties;
 *       3: Undefined behavior;
 * Ignore the undefined options automatically
 */
char getMode(std::string arg)
{
    char mask = 0;
    for (auto i : arg) {
        if (i == 'a')
            mask |= 0b10000000;
        else if (i == 'c')
            mask |= 0b01000000;
        else if (i == 'r')
            mask |= 0b00100000;
        else if (i == 't')
            mask |= 0b00010000;
        else if (i == 'u')
            mask |= 0b00001000;
        else if (i == 'x')
            mask |= 0b00000100;
        else if (i == 'v' && (mask & 3) ^ 2)
            mask++;
    }
    return mask;
}

char parser(int argc, char *argv[])
{
    if (IS_NEED_HELP(argc, argv))
        needHelp(std::string(argv[0]));
    else if (argc == 2)
        needHelp(std::string(argv[0]));
    return getMode(std::string(argv[1]));
}

#endif