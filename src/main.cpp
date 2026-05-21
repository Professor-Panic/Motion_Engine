#include "raylib.h"
#include "raymath.h"
#include "json/json.hpp"
#include "string"
#include <iostream>
#include <vector>
#include "fstream"
using namespace nlohmann;
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
std::pair<int, int> FindKeyframeIndices(const std::vector<float>& keyframes, float t)
{
    int n = (int)keyframes.size();

    if (n == 0)
        return {-1, -1};

    // Before first keyframe
    if (t <= keyframes[0])
        return {0, 0};

    // After last keyframe
    if (t >= keyframes[n - 1])
        return {n - 1, n - 1};

    // Find interval
    for (int i = 0; i < n - 1; i++)
    {
        if (t >= keyframes[i] && t <= keyframes[i + 1])
        {
            return {i, i + 1};
        }
    }

    // Fallback (should never happen if data is valid)
    return {n - 1, n - 1};
}
void ParseCircles(json animFile,AnimData& anim){
    float duration=0.0;
    if(animFile.contains("Duration")){
        duration=animFile["Duration"];
    }
    anim.duration=duration;
    if(animFile.contains("Objects")){
        for(auto& obj:animFile["Objects"]){
            if(obj["type"]=="Circle"){
                Circle c;
                for(auto&Keyframes:obj["Keyframes"]){
                    float t=Keyframes["t"];
                    Vector2 position={float(Keyframes["Position"][0]),float(Keyframes["Position"][1])};
                    Color col={(unsigned char)Keyframes["Color"][0],
                            (unsigned char)Keyframes["Color"][1],
                            (unsigned char)Keyframes["Color"][2],
                            (unsigned char)Keyframes["Color"][3],
                           };
                    float scale=Keyframes["Scale"][0];
                    c.positions.push_back(position);
                    c.scales.push_back(scale);
                    c.colors.push_back(col);
                    c.keyframes.push_back(t);
                }
                anim.circles.push_back(c);
            }
        }
    }
}
Vector2 ToScreenSpace(Vector2 v, Vector2 screenSize)
{
    float x = (v.x + 1.0f) * 0.5f * screenSize.x;
    float y = (1.0f - (v.y + 1.0f) * 0.5f) * screenSize.y;

    return { x, y };
}
void Update(AnimData& anim,float t){
    for(auto&circle:anim.circles){
        auto [k0,k1] = FindKeyframeIndices(circle.keyframes, t);

        float t0 = circle.keyframes[k0];
        float t1 = circle.keyframes[k1];

        float dt = t1 - t0;

        float alpha = 0.0f;
        if (dt != 0.0f)
            alpha = (t - t0) / dt;

        Vector2 pos = Vector2Lerp(circle.positions[k0], circle.positions[k1], alpha);
        float scale=Lerp(circle.scales[k0],circle.scales[k1],alpha);
        pos = ToScreenSpace(pos, Vector2{1200,800});
        Color col = ColorLerp(circle.colors[k0], circle.colors[k1], alpha);

        DrawCircleV(pos, 50*scale, col);

    }
}
int main(){
     AnimData anim;
    std::fstream f("C:/Users/Professor Panic/Documents/Coding_Projects/Raylib_Projects/Ray Canvas/assets/test.json");
    json animFile=json::parse(f);
    ParseCircles(animFile,anim);
    InitWindow(1200,800,"RayCanvas");
    SetTargetFPS(60);
    float time=0.0;
    while (!WindowShouldClose()){
        time+=GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        Update(anim,time);
        EndDrawing();
        if(time>anim.duration){
            break;
        }
    }
    CloseWindow();
}