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
    if (!!tag)  // in the TAG, except for EMPTY
        word = string(magic_enum::enum_name(tag));
    Type typeMask(word);
    // If is a type overwrite with type, else remain the origin
    word = typeMask.getType();
    return word;
}


#endif