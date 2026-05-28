#include "updater/updater.h"
void Update(AnimData& anim,float t){
    int counter=0;
    for(auto&circle:anim.circles){
        auto [k0,k1] = FindKeyframeIndices(circle.keyframes, t);

        float t0 = circle.keyframes[k0];
        float t1 = circle.keyframes[k1];
        float alpha = InverseLerp(t0,t1,t);
        Vector2 pos=Vector2Zero();
        if(circle.transforms[k0].trans_position.interPolation==0){
            pos=Vector2Lerp(circle.transforms[k0].trans_position.position,circle.transforms[k1].trans_position.position,alpha);
        }
        if(circle.transforms[k0].trans_position.interPolation==1){
            pos=Vector2Step(alpha,0.3,circle.transforms[k0].trans_position.position,circle.transforms[k1].trans_position.position);
        }
        Vector2 scale=Vector2Zero();
        if(circle.transforms[k0].trans_scale.interPolation==0){
            scale=Vector2Lerp(circle.transforms[k0].trans_scale.scale,circle.transforms[k1].trans_scale.scale,alpha);
        }
        pos = ToScreenSpace(pos,raster_size);
        Color col ={0,0,0,0};
        if(circle.transforms[k0].trans_color.interPolation==0){
         col=ColorLerp(circle.transforms[k0].trans_color.color, circle.transforms[k1].trans_color.color, alpha);
        }
        if(circle.transforms[k0].trans_color.interPolation==1){
         col=ColorStep(alpha,0.5,circle.transforms[k0].trans_color.color, circle.transforms[k1].trans_color.color);
        }
        DrawCircleV(pos, 50*scale.x, col);
    }
    for(auto&text:anim.texts){
        if(t<text.keyframes[0]){
            continue;
        }
        auto [k0,k1] = FindKeyframeIndices(text.keyframes, t);

        float t0 = text.keyframes[k0];
        float t1 = text.keyframes[k1];

        float alpha =InverseLerp(t0,t1,t);
        Vector2 pos = Vector2Lerp(text.positions[k0], text.positions[k1], alpha);
        float fontSize=Lerp(text.fontsizes[k0],text.fontsizes[k1],alpha);
        Color col = ColorLerp(text.colors[k0], text.colors[k1], alpha);
        EngineDrawTextLines(text.textPath,fontSize,pos,col);
    }
}