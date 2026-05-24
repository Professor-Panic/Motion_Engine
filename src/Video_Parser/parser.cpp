#include "Video_Parser/parser.h"
void ParseCircles(nlohmann::json &animFile,AnimData& anim){
    float duration=0.0;
    if(animFile.contains("Duration")){
        duration=animFile["Duration"];
    }
    anim.duration=duration;
    if(animFile.contains("Objects")){
        for(auto& obj:animFile["Objects"]){
            if(obj["type"]=="Circle"){
                Circle c;
                Vector2 currentPosition;
                Color currentColor;
                float currentScale;
                for(int i=0;i<obj["Keyframes"].size();i++){
                    auto&Keyframes=obj["Keyframes"][i];
                    float t=Keyframes["t"];
                    if(Keyframes.contains("Position")){
                        currentPosition={float(Keyframes["Position"][0]),float(Keyframes["Position"][1])};     
                    }
                    if(Keyframes.contains("Color")){
                        currentColor={(unsigned char)Keyframes["Color"][0],
                            (unsigned char)Keyframes["Color"][1],
                            (unsigned char)Keyframes["Color"][2],
                            (unsigned char)Keyframes["Color"][3],
                           };
                    }
                    if(Keyframes.contains("Scale")){
                        currentScale=Keyframes["Scale"][0];
                    }
                   
                    c.positions.push_back(currentPosition);
                    c.scales.push_back(currentScale);
                    c.colors.push_back(currentColor);
                    c.keyframes.push_back(t);
                }
                anim.circles.push_back(c);
            }
        }
    }
}
void ParseText(nlohmann::json &animFile,AnimData& anim,TTFFontParser::FontData &font_data,float fontSize){
    if(animFile.contains("Objects")){
        for(auto& obj:animFile["Objects"]){
            if(obj["type"]=="Text"){
                Text text;
                std::string text_str=obj["Text"];
                TraceLog(LOG_INFO,text_str.c_str());
                Vector2 currentPosition;
                Color currentColor;
                float currentScale;
                float currentFontsize;
                WordPath path=GetPathsForText(TextFormat(text_str.c_str()),font_data,fontSize);
                for(int i=0;i<obj["Keyframes"].size();i++){
                    auto&Keyframes=obj["Keyframes"][i];
                    float t=Keyframes["t"];
                    if(Keyframes.contains("Position")){
                        currentPosition={float(Keyframes["Position"][0]),float(Keyframes["Position"][1])};     
                    }
                    if(Keyframes.contains("Color")){
                        currentColor={(unsigned char)Keyframes["Color"][0],
                            (unsigned char)Keyframes["Color"][1],
                            (unsigned char)Keyframes["Color"][2],
                            (unsigned char)Keyframes["Color"][3],
                           };
                    }
                    if(Keyframes.contains("Scale")){
                        currentScale=Keyframes["Scale"][0];
                    }
                    if(Keyframes.contains("Fontsize")){
                        currentFontsize=Keyframes["Fontsize"];
                    }
                    text.textPath=path;
                    text.positions.push_back(currentPosition);
                    text.scales.push_back(currentScale);
                    text.colors.push_back(currentColor);
                    text.keyframes.push_back(t);
                }
                anim.texts.push_back(text);
            }
        }
    }
}
