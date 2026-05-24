#include "extras.h"
Vector2 ToScreenSpace(Vector2 v, Vector2 screenSize)
{
    float x = (v.x + 1.0f) * 0.5f * screenSize.x;
    float y = (1.0f - (v.y + 1.0f) * 0.5f) * screenSize.y;

    return { x, y };
}
std::pair<int, int> FindKeyframeIndices(const std::vector<float>& keyframes, float t)
{
    int n = (int)keyframes.size();

    if (n == 0)
        return {-1, -1};

    // Before first keyframe
    if (t <= keyframes[0])
        return {0, 0};

    // After last keyframe
    if (t >= keyframes[n - 1])
        return {n - 1, n - 1};

    // Find interval
    for (int i = 0; i < n - 1; i++)
    {
        if (t >= keyframes[i] && t <= keyframes[i + 1])
        {
            return {i, i + 1};
        }
    }

    // Fallback (should never happen if data is valid)
    return {n - 1, n - 1};
}
Vector2 BezierInterpolation(Vector2 p0,Vector2 p1,Vector2 c,float t){
    Vector2 p3=Vector2Lerp(p0,c,t);
    Vector2 p4=Vector2Lerp(c,p1,t);
    return Vector2Lerp(p3,p4,t);
}
void EngineDrawLineBezier(Vector2 p0,Vector2 p1,Vector2 c,int resolution,Color color){
    Vector2 prevPoint=p0;
    if(resolution<0){
        std::cout<<"Resolution mut be greater than 0 \n";
    }
    for(int i=0;i<resolution;i++){
        float t=float(i+1)/float(resolution);
        Vector2 nextPoint=BezierInterpolation(p0,p1,c,t);
        DrawLineV(prevPoint,nextPoint,color);
        prevPoint=nextPoint;
    }
}
void EngineDrawTextLines(WordPath paths,float fontSize,Color color){
    Vector2 offset=Vector2Zero();
        for(auto& path:paths.wordpaths){
            for(auto&points:path.geometry){

                Vector2 p=ToScreenSpace(Vector2Scale(points.p0+offset,fontSize),raster_size);
                Vector2 p1=ToScreenSpace(Vector2Scale(points.p1+offset,fontSize),raster_size);
                Vector2 c=ToScreenSpace(Vector2Scale(points.c+offset,fontSize),raster_size);
                if(points.isCurve){
                    EngineDrawLineBezier(p,c,p1,10,color);
                }
                else{
                    DrawLineV(p,p1,color);
                }
            }
            offset+=path.offset;
        }
}