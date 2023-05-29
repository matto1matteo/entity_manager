#pragma once
#include <ostream>

class Vec2 {
public:
    Vec2() = default;
    Vec2(Vec2 &&) = default;
    Vec2(const Vec2 &) = default;
    Vec2 &operator=(Vec2 &&) = default;
    Vec2 &operator=(const Vec2 &) = default;
    ~Vec2() = default;

    Vec2(float x, float y);
    static Vec2 FromSpeedAndAngle(float speed, float angle);

    float x = 0;
    float y = 0;

public:
    bool operator == (const Vec2 & rhs) const;
    bool operator != (const Vec2 & rhs) const;

    Vec2 operator + (const Vec2 & rhs) const;
    Vec2 operator - (const Vec2 & rhs) const;
    Vec2 operator / (const float rhs) const;
    Vec2 operator * (const float rhs) const;

    void operator += (const Vec2 & rhs);
    void operator -= (const Vec2 & rhs);
    void operator /= (const float rhs);
    void operator *= (const float rhs);

    float dist(const Vec2 & rhs) const;

    float length() const;

    void normalize();
    Vec2 normalized() const;

    float getAngle() const;

    friend std::ostream & operator << (std::ostream & out, const Vec2 vec);

private:
    
};
