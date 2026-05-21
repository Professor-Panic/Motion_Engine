#pragma once
#include "raylib.h"
#include <utility>
#include <vector>
Vector2 ToScreenSpace(Vector2 v, Vector2 screenSize);
std::pair<int, int> FindKeyframeIndices(const std::vector<float>& keyframes, float t);