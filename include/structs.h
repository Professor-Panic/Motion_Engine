#pragma once
#include "raylib.h"
#include <vector>
struct Circle{
    std::vector<Vector2>positions;
    std::vector<float> scales;
    std::vector<Color> colors;
    std::vector<float>keyframes;
};
struct AnimData
{
    std::vector<Circle>circles;
    float duration;
};