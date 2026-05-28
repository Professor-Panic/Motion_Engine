#pragma once
#include "raylib.h"
float InverseLerp(float t0,float t1,float t);
float Step(float t,float threshold);
Vector2 Vector2Step(float t,float threshold,Vector2&min,Vector2 max);
Color ColorStep(float t,float threshold,Color&min,Color max);