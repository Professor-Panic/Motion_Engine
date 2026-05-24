#pragma once
#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "structs.h"
#include <utility>
#include <iostream>
#include <vector>

Vector2 ToScreenSpace(Vector2 v, Vector2 screenSize);
std::pair<int, int> FindKeyframeIndices(const std::vector<float>& keyframes, float t);
Vector2 BezierInterpolation(Vector2 p0,Vector2 p1,Vector2 c,float t);
void EngineDrawLineBezier(Vector2 p0,Vector2 p1,Vector2 c,int resolution,Color color);
void EngineDrawTextLines(WordPath paths,Color color);