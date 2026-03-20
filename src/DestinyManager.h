#pragma once
#include <array>
#include <utility>
#include "GameConfig.h"
#include <random>

class DestinyManager
{
    private:
        struct Position
        {
            float x;
            float y;
        };

    public:
        DestinyManager();
        void Reset();
        void AddPosition(float x, float y);
        void GetRandomPosition(float& x, float& y);
        int GetTotalPositions() const;

    private:
    std::array<Position, PLANES_POOL_SIZE> _positions;
    int _lastPosition;
    std::mt19937 _generator;
};