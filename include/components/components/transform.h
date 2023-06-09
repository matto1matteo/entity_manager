#pragma once

#include <geometry/vec2.h>

class CTransform {
public:
    Vec2 pos = { 0.0f, 0.0f };
    Vec2 velocity = { 0.0f, 0.0f };
    float angle = 0.0f;

    CTransform(const Vec2 & pos, const Vec2 & velocity, float a)
        : pos(pos)
        , velocity(velocity)
        , angle(a)
    {}

private:
};
