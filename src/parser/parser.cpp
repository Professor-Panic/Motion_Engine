#include "parser/parser.h"
void ParseCircles(nlohmann::json animFile,AnimData& anim){
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