#pragma once
#include <array>
#include <utility>
#include "GameConfig.h"
#include <random>

class RandomManager
{
    public:
        RandomManager();
        float GetValue(float min, float max);
        int GetValue(int min, int max);
        int GetNextIntValue();
        float GetNextFloatValue();
        std::default_random_engine& GetGenerator();

    private:
    std::default_random_engine _generator;
};