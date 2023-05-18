#include <geometry/vec2.h>

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{
}

bool Vec2::operator == (const Vec2 & rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool Vec2::operator != (const Vec2 & rhs) const
{
    return this->x != rhs.x || this->y != rhs.y;
}

Vec2 Vec2::operator + (const Vec2 & rhs) const
{
    return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
    return Vec2(this->x - rhs.x, this->y - rhs.y);
}
