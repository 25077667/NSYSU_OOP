#include "type.hpp"


Type max(const Type &t1, const Type &t2)
{
    const auto w = std::max(t1.width, t2.width);
    return (w == t1.width) ? Type(t1.lexeme, t1.width)
                           : Type(t2.lexeme, t2.width);
}