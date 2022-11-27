#include "rayextended.h"
#include "raylib.h"
#include <cmath>

Vector2 operator-(const Vector2& a)
{ return {-a.x, -a.y}; }

Vector2 operator+(const Vector2& a, const Vector2& b)
{ return {a.x + b.x, a.y + b.y}; }
Vector2 operator-(const Vector2& a, const Vector2& b)
{ return {a.x - b.x, a.y - b.y}; }
Vector2 operator*(const Vector2& a, const Vector2& b)
{ return {a.x * b.x, a.y * b.y}; }
Vector2 operator/(const Vector2& a, const Vector2& b)
{ return {a.x / b.x, a.y / b.y}; }

Vector2& operator+=(Vector2& a, const Vector2& b)
{ return a = a + b; }
Vector2& operator-=(Vector2& a, const Vector2& b)
{ return a = a - b; }
Vector2& operator*=(Vector2& a, const Vector2& b)
{ return a = a * b; }
Vector2& operator/=(Vector2& a, const Vector2& b)
{ return a = a / b; }

Vector2 operator+(const float& a, const Vector2& b)
{ return {Vector2{a, a} + b}; }
Vector2 operator-(const float& a, const Vector2& b)
{ return {Vector2{a, a} - b}; }
Vector2 operator*(const float& a, const Vector2& b)
{ return {Vector2{a, a} * b}; }
Vector2 operator/(const float& a, const Vector2& b)
{ return {Vector2{a, a} / b}; }

Vector2 operator+(const Vector2& a, const float& b)
{ return b + a; }
Vector2 operator-(const Vector2& a, const float& b)
{ return {a - Vector2{b, b}}; }
Vector2 operator*(const Vector2& a, const float& b)
{ return b * a; }
Vector2 operator/(const Vector2& a, const float& b)
{ return {a / Vector2{b, b}}; }

Vector2& operator+=(Vector2& a, const float& b)
{ return a = a + b; }
Vector2& operator-=(Vector2& a, const float& b)
{ return a = a - b; }
Vector2& operator*=(Vector2& a, const float& b)
{ return a = a * b; }
Vector2& operator/=(Vector2& a, const float& b)
{ return a = a / b; }


bool operator==(const Vector2& a, const Vector2& b)
{ return a.x == b.x && a.y == b.y; }
bool operator!=(const Vector2& a, const Vector2& b)
{ return a.x != b.x || a.y != b.y; }

Vector2 vecAbs(const Vector2& a)
{ return {std::abs(a.x), std::abs(a.y)}; }
// this could be optimized with a faster sqrt func
float vec2distance(const Vector2& a, const Vector2& b)
{ return std::sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) ); } 
float lowerLimitFrameTime()
{
    if (GetFrameTime() > 0.0667)
        return 0.0667;
    return GetFrameTime();
}
float vec2ToFloat(Vector2 x)
{
    return vec2distance(x, {0, 0});
}
float vec2ToAngle(Vector2 x)
{
    float output{atanf(x.y/x.x) * RAD2DEG};
    if (x.x < 0) output += 180;
    else if (x.y < 0) output += 360;
    return output;
}
Vector2 floatAngleToVec2(float x, float angle)
{
    return {cosf(angle * DEG2RAD) * x, sinf(angle * DEG2RAD) * x};
}