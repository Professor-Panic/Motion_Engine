#include "raylib.h"
#include "raymath.h"
#include "json/json.hpp"
#include "string"
#include <iostream>
#include "parser/parser.h"
#include "updater/updater.h"
#include "structs.h"
#include "extras.h"
#include "fstream"
using namespace nlohmann;

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