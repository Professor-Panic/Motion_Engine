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
#define TTF_FONT_PARSER_IMPLEMENTATION
#include "ttfparser/ttfparser.h"
#include "Font_Parser/font_parser.h"
int main(){
    Vector2 raster_size={1200,800};
    uint8_t condition=0;
    AnimData anim;
    int font_size=20;
    std::fstream f("C:/Users/Professor Panic/Documents/Coding_Projects/Raylib_Projects/Ray Canvas/assets/test.json");
    json animFile=json::parse(f);
    TTFFontParser::FontData font_data;
    int error=TTFFontParser::parse_file(TextFormat("times.ttf"),&font_data,&font_parsed,&condition);
    WordPath paths=GetPathsForText(TextFormat("Hi my name is Tedd!"),font_data,0.0);
    ParseCircles(animFile,anim);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1200,800,"RayCanvas");
    SetTargetFPS(60);
    float time=0.0;
    Vector2 LetterSpacing={1.0,0};
    while (!WindowShouldClose()){
        time+=GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        Update(anim,time);
        Vector2 offset=Vector2Zero();
        for(auto& path:paths.wordpaths){
            for(auto&points:path.geometry){
                Vector2 p=ToScreenSpace(points.p0+offset,raster_size);
                Vector2 p1=ToScreenSpace(points.p1+offset,raster_size);
                Vector2 c=ToScreenSpace(points.c+offset,raster_size);
                std::cout<<p.x<< ","<<p.y<<std::endl;
                if(points.isCurve){
                    EngineDrawLineBezier(p,c,p1,10,WHITE);
                }
                else{
                    DrawLineV(p,p1,WHITE);
                }
            }
            offset+=path.offset;
            offset.x*=LetterSpacing.x;
        }
        EndDrawing();
        if(time>anim.duration){
            break;
        }
    }
    CloseWindow();
}