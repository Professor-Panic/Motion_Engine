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
                EngineTransform currentTransform;
                for(int i=0;i<obj["Keyframes"].size();i++){
                    auto&Keyframes=obj["Keyframes"][i];
                    float t=Keyframes["t"];
                    if(Keyframes.contains("Position")){
                        if(Keyframes["Position"].contains("Values")){
                              currentTransform.trans_position.position={float(Keyframes["Position"]["Values"][0]),float(Keyframes["Position"]["Values"][1])};
                        }
                        if(Keyframes["Position"].contains("Interpolation")){
                            currentTransform.trans_position.interPolation=Keyframes["Position"]["Interpolation"];
                        }
                        else{
                            currentTransform.trans_position.interPolation=0;   
                        }
                    }
                    if(Keyframes.contains("Color")){
                        if(Keyframes["Color"].contains("Values")){
                             currentTransform.trans_color={(unsigned char)Keyframes["Color"]["Values"][0],
                            (unsigned char)Keyframes["Color"]["Values"][1],
                            (unsigned char)Keyframes["Color"]["Values"][2],
                            (unsigned char)Keyframes["Color"]["Values"][3],
                           };
                        }
                        if(Keyframes["Color"].contains("Interpolation")){
                            currentTransform.trans_color.interPolation=Keyframes["Color"]["Interpolation"];
                        }
                        else{
                            currentTransform.trans_color.interPolation=0;   
                        }
                    }
                    if(Keyframes.contains("Scale")){
                        if(Keyframes["Scale"].contains("Values")){
                            currentTransform.trans_scale.scale={Keyframes["Scale"]["Values"][0],0};
                        }
                        if(Keyframes["Scale"].contains("Interpolation")){
                            currentTransform.trans_scale.interPolation=Keyframes["Scale"]["Interpolation"];
                        }
                        else{
                            currentTransform.trans_scale.interPolation=0;   
                        }
                    }
                   
                    c.transforms.push_back(currentTransform);
                    c.keyframes.push_back(t);
                }
                anim.circles.push_back(c);
            }
        }
    }
}
void ParseText(nlohmann::json &animFile,AnimData& anim,TTFFontParser::FontData &font_data){
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
                WordPath path=GetPathsForText(TextFormat(text_str.c_str()),font_data,1.0);
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
                    text.fontsizes.push_back(currentFontsize);
                    text.colors.push_back(currentColor);
                    text.keyframes.push_back(t);
                }
                anim.texts.push_back(text);
            }
        }
    }
}
