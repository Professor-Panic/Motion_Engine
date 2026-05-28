#include "Math/math.h"
float InverseLerp(float t0,float t1,float t){
    float dt = t1 - t0;

    float alpha = 0.0f;
    if (dt != 0.0f)
        alpha = (t - t0) / dt;
    return alpha;
}
float Step(float t,float threshold,float min=0.0,float max=1.0){
     if(t<=threshold){
        return min;
     }
     else{
        return max;
     }
}
Vector2 Vector2Step(float t,float threshold,Vector2&min,Vector2 max){
    if(t<=threshold){
        return min;
    }
    else{
        return max;
    }
}
Color ColorStep(float t,float threshold,Color&min,Color max){
    if(t<=threshold){
        return min;
    }
    else{
        return max;
    }
}