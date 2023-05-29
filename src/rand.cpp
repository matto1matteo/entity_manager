#include <rand/random.hpp>
#include <ctime>

namespace mtt
{

void seed()
{
    std::srand(std::time(0));
}

int randRange(int lowerBound, int upperBound)
{
    return lowerBound + std::rand() % (upperBound - lowerBound);
}

int nextInt()
{
    return randRange(0, RAND_MAX);
}
    

int randRange(int upperBound)
{
    return randRange(0, upperBound);
}

float randRange(float lowerBound, float upperBound)
{
    return lowerBound + static_cast<float>(std::rand())
        / (static_cast<float>(RAND_MAX)/(upperBound - lowerBound));
}

float randRange(float upperBound)
{
    return randRange(0.0f, upperBound);
}

float nextFloat()
{
    return randRange((float)RAND_MAX);
}

}

