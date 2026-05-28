#include "Math/math.h"
float InverseLerp(float t0,float t1,float t){
    float dt = t1 - t0;

    float alpha = 0.0f;
    if (dt != 0.0f)
        alpha = (t - t0) / dt;
    return alpha;
}
float Step(float t,float threshold){
     if(t<=threshold){
        return 0.0;
     }
     else{
        return 1.0;
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
float EaseInOutBack(float x){
const float c1 = 1.70158;
const float c2 = c1 * 1.525;

return x < 0.5
  ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
  : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}