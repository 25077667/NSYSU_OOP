// Tag's implementation
// To specify the them

#ifndef WORD_HPP
#define WORD_HPP
#include <iostream>
#include "magic_enum.hpp"
#include "tag.hpp"
#include "type.hpp"
using namespace std;

string getWord(string_view lexeme, Tag tag)
{
    string word = string(lexeme);
    if (!!tag)  // in the TAG
        word = string(magic_enum::enum_name(tag));
    return word;
}


#endif