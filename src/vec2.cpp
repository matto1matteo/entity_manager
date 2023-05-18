#include <geometry/vec2.h>
#include <math.h>

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{
}

Vec2 Vec2::FromSpeedAndAngle(float speed, float angle)
{
    float x = speed * cos(angle);
    float y = speed * sin(angle);
    return Vec2(x, y);
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
