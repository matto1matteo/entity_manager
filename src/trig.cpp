#include <trig/trig.hpp>
#include <cmath>

namespace mtt
{
float fromRad(float teta)
{
    return teta * 180 / M_PI;
}

float toRad(float teta)
{
    return teta * M_PI / 180;
}
}
