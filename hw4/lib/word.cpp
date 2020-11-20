#include "word.hpp"
#include "magic_enum.hpp"
#include "tag.hpp"
#include "type.hpp"
using namespace std;

extern bool operator!(Tag tag);

string getWord(string lexeme, Tag tag)
{
    Type typeMask(lexeme.c_str());
    // If is a type overwrite with type, else remain the origin
    if (typeMask)
        return string(typeMask.getType());
    else if (!!tag)  // in the TAG, except for EMPTY
        return string(magic_enum::enum_name(tag));
    else
        return lexeme;
}