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