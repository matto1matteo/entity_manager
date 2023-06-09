#pragma once

class Vec2 {
public:
    Vec2() = default;
    Vec2(Vec2 &&) = default;
    Vec2(const Vec2 &) = default;
    Vec2 &operator=(Vec2 &&) = default;
    Vec2 &operator=(const Vec2 &) = default;
    ~Vec2() = default;

    Vec2(float x, float y);

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

private:
    
};
