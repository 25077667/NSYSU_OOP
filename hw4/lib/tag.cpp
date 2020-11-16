#include "tag.hpp"

bool operator!(Tag tag)
{
    return tag == static_cast<Tag>(0);
}