#include "RandomManager.h"
RandomManager::RandomManager():_generator(std::random_device{}()){}

float RandomManager::GetValue(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(_generator);
}

int RandomManager::GetValue(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(_generator);
}

int RandomManager::GetNextIntValue()
{
    return static_cast<int>(_generator());
}

float RandomManager::GetNextFloatValue()
{
    return static_cast<float>(_generator());
}

std::default_random_engine& RandomManager::GetGenerator()
{
    return _generator;
}