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
void EngineDrawLineBezier(Vector2 p0,Vector2 p1,Vector2 c,int resolution,Color color){
    Vector2 prevPoint=p0;
    if(resolution<0){
        std::cout<<"Resolution mut be greater than 0";
    }
    for(int i=0;i<=resolution;i++){
        float t=float(i+1)/float(resolution);
        Vector2 nextPoint=BezierInterpolation(p0,p1,c,t);
        DrawLineV(prevPoint,nextPoint,color);
        prevPoint=nextPoint;
    }
}
int main(){
    Vector2 raster_size={1200,800};
    uint8_t condition=0;
    AnimData anim;
    int font_size=20;
    std::fstream f("C:/Users/Professor Panic/Documents/Coding_Projects/Raylib_Projects/Ray Canvas/assets/test.json");
    json animFile=json::parse(f);
    TTFFontParser::FontData font_data;
    int error=TTFFontParser::parse_file(TextFormat("times.ttf"),&font_data,&font_parsed,&condition);
    std::vector<TTFFontParser::Path>paths=font_data.glyphs[66].path_list;
    float unitsPerEm=float(font_data.meta_data.unitsPerEm);
    Path c_path;
    for(auto& path:paths){
        std::cout<<path.geometry.size()<<std::endl;
        for(auto &curve:path.geometry){
            Curves c_curve;
            c_curve.c={curve.c.x,curve.c.y};
            c_curve.c=Vector2Scale(c_curve.c,(1/unitsPerEm));
            c_curve.p0={curve.p0.x,curve.p0.y};
            c_curve.p0=Vector2Scale(c_curve.p0,(1/unitsPerEm));
            TraceLog(LOG_INFO,TextFormat("%.1f,%.1f",c_curve.p0.x,c_curve.p0.y));
            c_curve.p1={curve.p1.x,curve.p1.y};
            c_curve.p1=Vector2Scale(c_curve.p1,(1/unitsPerEm));
            c_curve.isCurve=curve.is_curve;
            c_curve.needsMidpoint=curve.needsMidpoint;
            c_path.geometry.push_back(c_curve);

        }
    }
    ParseCircles(animFile,anim);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1200,800,"RayCanvas");
    SetTargetFPS(60);
    float time=0.0;
    while (!WindowShouldClose()){
        time+=GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        Update(anim,time);
        for(int i=0;i<c_path.geometry.size();i++){
            auto &points=c_path.geometry[i];
            Vector2 p=ToScreenSpace(points.p0,raster_size);
            Vector2 p1=ToScreenSpace(points.p1,raster_size);
            Vector2 c=ToScreenSpace(points.c,raster_size);
            Vector2 prev=p;
            if(i>0){
                prev=ToScreenSpace(c_path.geometry[i-1].p1,raster_size);
            }
            if(points.isCurve){
                EngineDrawLineBezier(p,c,p1,10,WHITE);
            }
            else{
                  DrawLineV(p,p1,RED);
            }
        }
        EndDrawing();
        if(time>anim.duration){
            break;
        }
    }
    CloseWindow();
}