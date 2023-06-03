#include <geometry/vec2.h>
#include <math.h>

Vec2::Vec2(float x, float y)
    : x(x)
    , y(y)
{
}

Vec2 Vec2::FromSpeedAndAngle(float speed, float angle)
{
    float teta = (angle * M_PI) / 180;
    float x = speed * sin(teta);
    float y = speed * cos(teta);
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

void Vec2::operator += (const Vec2 & rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator -= (const Vec2 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

Vec2 Vec2::operator / (const float rhs) const
{
    return Vec2(x / rhs, y / rhs);
}

Vec2 Vec2::operator * (const float rhs) const
{
    return Vec2(x * rhs, y * rhs);
}

void Vec2::operator /= (const float rhs)
{
    x /= rhs;
    y /= rhs;
}

void Vec2::operator *= (const float rhs)
{
    x *= rhs;
    y *= rhs;
}

float Vec2::dist(const Vec2 & rhs) const
{
    float xdist = x - rhs.x;
    float ydist = y - rhs.y;
    return sqrt((xdist * xdist) + (ydist * ydist));
}

float Vec2::length() const
{
    return sqrt(x*x + y*y);
}

void Vec2::normalize()
{
    float len = length();
    x /= len;
    y /= len;
}

Vec2 Vec2::normalized() const
{
    float len = length();
    return Vec2(x / len, y / len);
}

float Vec2::getAngle() const
{
    float teta = abs(atan(abs(x / y))) * 180 / M_PI;
    if (x >= 0 && y >= 0)
    {
        return teta;
    }
    else if (x < 0 && y >= 0)
    {
        return 360 - teta;
    }
    else if (x < 0 && y < 0)
    {
        return 180 + teta;
    }
    return 180 - teta;
}


std::ostream & operator << (std::ostream & out, const Vec2 vec)
{
    out << "Vec2(x: " << vec.x << ", y: " << vec.y << ")";
    return out;
}
