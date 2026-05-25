#include "updater/updater.h"
void Update(AnimData& anim,float t){
    int counter=0;
    for(auto&circle:anim.circles){
        auto [k0,k1] = FindKeyframeIndices(circle.keyframes, t);

        float t0 = circle.keyframes[k0];
        float t1 = circle.keyframes[k1];

        float dt = t1 - t0;

        float alpha = 0.0f;
        if (dt != 0.0f)
            alpha = (t - t0) / dt;

        Vector2 pos = Vector2Lerp(circle.positions[k0], circle.positions[k1], alpha);
        float scale=Lerp(circle.scales[k0],circle.scales[k1],alpha);
        pos = ToScreenSpace(pos, Vector2{1200,800});
        Color col = ColorLerp(circle.colors[k0], circle.colors[k1], alpha);

        DrawCircleV(pos, 50*scale, col);
    }
    for(auto&text:anim.texts){
        if(t<text.keyframes[0]){
            continue;
        }
        auto [k0,k1] = FindKeyframeIndices(text.keyframes, t);

        float t0 = text.keyframes[k0];
        float t1 = text.keyframes[k1];

        float dt = t1 - t0;

        float alpha = 0.0f;
        if (dt != 0.0f)
            alpha = (t - t0) / dt;

        Vector2 pos = Vector2Lerp(text.positions[k0], text.positions[k1], alpha);
        float fontSize=Lerp(text.fontsizes[k0],text.fontsizes[k1],alpha);
        Color col = ColorLerp(text.colors[k0], text.colors[k1], alpha);
        EngineDrawTextLines(text.textPath,fontSize,pos,col);
    }
}