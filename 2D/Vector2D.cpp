#include "Vector2D.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
    os << " " << rhs.x_ << " " << rhs.y_;
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
    is >> lhs.x_ >> lhs.y_;
    return is;
}
