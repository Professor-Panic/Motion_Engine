#include "raylib.h"
#include "raymath.h"
#include "json/json.hpp"
#include "string"
#include <iostream>
#include "Video_Parser/parser.h"
#include "updater/updater.h"
#include "structs.h"
#include "extras.h"
#include "fstream"
using namespace nlohmann;
#include "Font_Parser/font_parser.h"
#include "ttfparser/ttfparser.h"
int main(){
    uint8_t condition=0;
    AnimData anim;
    std::fstream f("C:/Users/Professor Panic/Documents/Coding_Projects/Raylib_Projects/Ray Canvas/assets/test.json");
    json animFile=json::parse(f);
    TTFFontParser::FontData font_data;
    int error=TTFFontParser::parse_file(TextFormat("times.ttf"),&font_data,&font_parsed,&condition);
    ParseCircles(animFile,anim);
    ParseText(animFile,anim,font_data);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(raster_size.x,raster_size.y,"RayCanvas");
    SetTargetFPS(60);
    float time=0.0;
    while (!WindowShouldClose()){
        time+=GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        Update(anim,time);
        DrawText(TextFormat("%.2f",time),20,20,20,WHITE);
        EndDrawing();
        if(time>anim.duration){
            break;
        }
    }
    CloseWindow();
}