#pragma once

#include <geometry/vec2.h>

/// @brief  Component class used to store data about entity transformations
class CTransform {
public:
    Vec2 position = { 0.0f, 0.0f };
    Vec2 velocity = { 0.0f, 0.0f };
    float angle = 0.0f;

    CTransform(const Vec2 & pos, const Vec2 & velocity, float a)
        : position(pos)
        , velocity(velocity)
        , angle(a)
    {}

private:
};
