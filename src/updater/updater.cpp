#include "updater/updater.h"
void Update(AnimData& anim,float t){
    int counter=0;
    for(auto&circle:anim.circles){
        auto [k0,k1] = FindKeyframeIndices(circle.keyframes, t);

        float t0 = circle.keyframes[k0];
        float t1 = circle.keyframes[k1];
        float alpha = InverseLerp(t0,t1,t);
        Vector2 pos=Vector2Zero();
        Vector2 scale=Vector2Zero();
        if(circle.transforms[k0].trans_position.interPolation==0){
            pos=Vector2Lerp(circle.transforms[k0].trans_position.position,circle.transforms[k1].trans_position.position,alpha);
        }
        if(circle.transforms[k0].trans_position.interPolation==1){
            alpha=Step(alpha,0.3);
            pos=Vector2Lerp(circle.transforms[k0].trans_position.position,circle.transforms[k1].trans_position.position,alpha);
        }
        if(circle.transforms[k0].trans_position.interPolation==2){
            alpha=EaseInOutBack(alpha);
            pos=Vector2Lerp(circle.transforms[k0].trans_position.position,circle.transforms[k1].trans_position.position,alpha);
        }
        if(circle.transforms[k0].trans_scale.interPolation==0){
            scale=Vector2Lerp(circle.transforms[k0].trans_scale.scale,circle.transforms[k1].trans_scale.scale,alpha);
        }
        if(circle.transforms[k0].trans_scale.interPolation==1){
            alpha=Step(alpha,0.3);
            scale=Vector2Lerp(circle.transforms[k0].trans_scale.scale,circle.transforms[k1].trans_scale.scale,alpha);
        }
        pos = ToScreenSpace(pos,raster_size);
        Color col ={0,0,0,0};
        if(circle.transforms[k0].trans_color.interPolation==0){
         col=ColorLerp(circle.transforms[k0].trans_color.color, circle.transforms[k1].trans_color.color, alpha);
        }
        if(circle.transforms[k0].trans_color.interPolation==1){
            alpha=Step(alpha,0.5);
            col=ColorLerp(circle.transforms[k0].trans_color.color, circle.transforms[k1].trans_color.color,alpha);
        }
        if(circle.transforms[k0].trans_color.interPolation==2){
            alpha=EaseInOutBack(alpha);
            col=ColorLerp(circle.transforms[k0].trans_color.color, circle.transforms[k1].trans_color.color,alpha);
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
        Vector2 pos=Vector2Zero();
        Vector2 scale=Vector2Zero();
        if(text.transforms[k0].trans_position.interPolation==0){
            pos=Vector2Lerp(text.transforms[k0].trans_position.position,text.transforms[k1].trans_position.position,alpha);
        }
        if(text.transforms[k0].trans_position.interPolation==1){
            alpha=Step(alpha,0.3);
            pos=Vector2Lerp(text.transforms[k0].trans_position.position,text.transforms[k1].trans_position.position,alpha);
        }
        if(text.transforms[k0].trans_position.interPolation==2){
            alpha=EaseInOutBack(alpha);
            pos=Vector2Lerp(text.transforms[k0].trans_position.position,text.transforms[k1].trans_position.position,alpha);
        }
        if(text.transforms[k0].trans_scale.interPolation==0){
            scale=Vector2Lerp(text.transforms[k0].trans_scale.scale,text.transforms[k1].trans_scale.scale,alpha);
        }
        if(text.transforms[k0].trans_scale.interPolation==1){
            alpha=Step(alpha,0.3);
            scale=Vector2Lerp(text.transforms[k0].trans_scale.scale,text.transforms[k1].trans_scale.scale,alpha);
        }
        Color col ={0,0,0,0};
        if(text.transforms[k0].trans_color.interPolation==0){
         col=ColorLerp(text.transforms[k0].trans_color.color, text.transforms[k1].trans_color.color, alpha);
        }
        if(text.transforms[k0].trans_color.interPolation==1){
            alpha=Step(alpha,0.5);
            col=ColorLerp(text.transforms[k0].trans_color.color, text.transforms[k1].trans_color.color,alpha);
        }
        if(text.transforms[k0].trans_color.interPolation==2){
            alpha=EaseInOutBack(alpha);
            col=ColorLerp(text.transforms[k0].trans_color.color, text.transforms[k1].trans_color.color,alpha);
        }
        EngineDrawTextLines(text.textPath,scale.x,pos,col);
    }
}