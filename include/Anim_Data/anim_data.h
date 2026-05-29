#pragma once
#include "raylib.h"
#include <vector>
struct EnginePosition{
    Vector2 position;
    int interPolation;
};
struct EngineScale{
    Vector2 scale;
    int interPolation;
};
struct EngineColor{
    Color color;
    int interPolation;
};
struct EngineTransform{
    EnginePosition trans_position;
    EngineScale trans_scale;
    EngineColor trans_color;
};
struct Circle{
    std::vector<EngineTransform>transforms;
    std::vector<float>keyframes;
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
struct Text{
    WordPath textPath;
    std::vector<EngineTransform> transforms;
    std::vector<float>keyframes;
};
struct AnimData
{
    std::vector<Circle>circles;
    std::vector<Text>texts;
    float duration;
};