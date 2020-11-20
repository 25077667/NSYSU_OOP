#include "word.hpp"
#include <iostream>
#include "magic_enum.hpp"
#include "tag.hpp"
#include "type.hpp"
using namespace std;

extern bool operator!(Tag tag);

string getWord(string lexeme, Tag tag)
{
    string word(lexeme);
    if (!!tag)  // in the TAG, except for EMPTY
        word = string(magic_enum::enum_name(tag));
    Type typeMask(word);
    // If is a type overwrite with type, else remain the origin
    word = typeMask.getType();
    return word;
}