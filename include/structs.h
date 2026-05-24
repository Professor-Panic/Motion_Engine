#pragma once
#include "raylib.h"
#include <iostream>
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
struct Curves{
    Vector2 p0;
    Vector2 p1;
    Vector2 c;
    bool isCurve;
    bool needsMidpoint;
};
struct Path{
    std::vector<Curves>geometry;
    Vector2 offset;
};
struct WordPath{
    std::vector<Path>wordpaths;
};