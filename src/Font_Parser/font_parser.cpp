#include "Font_Parser/font_parser.h"
void ParsePath(Path& c_path,std::vector<TTFFontParser::Path>paths,float unitsPerEm,float fontSize){
    std::vector<Vector2>points;
    for(auto& path:paths){
        for(auto &curve:path.geometry){
            Curves c_curve;
            c_curve.c={curve.c.x,curve.c.y};
            c_curve.c=Vector2Scale(c_curve.c,(1/unitsPerEm)*((fontSize)/100.0));
            c_curve.p0={curve.p0.x,curve.p0.y};
            c_curve.p0=Vector2Scale(c_curve.p0,(1/unitsPerEm)*((fontSize)/100.0));
            c_curve.p1={curve.p1.x,curve.p1.y};
            c_curve.p1=Vector2Scale(c_curve.p1,(1/unitsPerEm)*((fontSize)/100.0));
            c_curve.isCurve=curve.is_curve;
            c_path.geometry.push_back(c_curve);
            points.push_back(c_curve.p1);
            points.push_back(c_curve.p0);
        }
    }
}
WordPath GetPathsForText(const char* text, TTFFontParser::FontData &font_data,float fontSize){
    unsigned int length=TextLength(text);
    float advance=0;
    WordPath paths;
    Vector2 offset={0,0};
    std::string str(text);
    for(int i=0;i<length;i++){
        std::vector<TTFFontParser::Path>path=font_data.glyphs[str[i]].path_list;
        advance=float(font_data.glyphs[str[i]].advance_width)/float(font_data.meta_data.unitsPerEm)*((fontSize)/100.0);
        if(str[i]==' '){
            advance=0.13*((fontSize)/100.0);
        }
        Path p;
        ParsePath(p,path,font_data.meta_data.unitsPerEm,fontSize);
        offset.x=advance;
        p.offset=offset;
        paths.wordpaths.push_back(p);
        TraceLog(LOG_INFO,TextFormat(" Offset: %.6f",advance));
    }
    return paths;
}