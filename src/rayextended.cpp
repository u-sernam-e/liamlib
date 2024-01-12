#include "rayextended.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>
#include <array>

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

bool operator==(const Color& a, const Color& b)
{ return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a; }
bool operator!=(const Color& a, const Color& b)
{ return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a;}

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
float getRandomFloat(float min, float max) { return static_cast<float>(GetRandomValue(static_cast<int>(min), static_cast<int>(max))); }
Vector2 getScreenSize() { return {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}; }

float vec2ToFloat(Vector2 x)
{
    return vec2distance(x, {0, 0});
}
float vec2ToAngle(Vector2 x)
{
    if (x == Vector2{0, 0})
        return 0;
    float output{atanf(x.y/x.x) * RAD2DEG};
    if (x.x < 0) output += 180;
    else if (x.y < 0) output += 360;
    return output;
}
Vector2 floatAngleToVec2(float x, float angle)
{
    return {cosf(angle * DEG2RAD) * x, sinf(angle * DEG2RAD) * x};
}
Vector2 getRotatedVec2(Vector2 vec2, Vector2 origin, float angle)
{
    return origin + floatAngleToVec2(vec2ToFloat(vec2-origin), vec2ToAngle(vec2-origin) + angle);
}
Vector2 getVec2AtAngle(Vector2 vec2, Vector2 origin, float angle)
{
    return origin + floatAngleToVec2(vec2ToFloat(vec2-origin), angle);
}
Vector2 normalizedVec2(Vector2 vec2)
{
    return floatAngleToVec2(1, vec2ToAngle(vec2));
}

Rectangle getRotatedRecBounds(Rectangle rec, float rot, Vector2 anchor)
{
    std::array<Vector2, 4> crnrs{
        floatAngleToVec2(vec2distance({rec.x, rec.y}, anchor), vec2ToAngle(Vector2{rec.x, rec.y} - anchor) + rot) + anchor,
        floatAngleToVec2(vec2distance({rec.x + rec.width, rec.y}, anchor), vec2ToAngle(Vector2{rec.x + rec.width, rec.y} - anchor) + rot) + anchor,
        floatAngleToVec2(vec2distance({rec.x + rec.width, rec.y + rec.height}, anchor), vec2ToAngle(Vector2{rec.x + rec.width, rec.y + rec.height} - anchor) + rot) + anchor,
        floatAngleToVec2(vec2distance({rec.x, rec.y + rec.height}, anchor), vec2ToAngle(Vector2{rec.x, rec.y + rec.height} - anchor) + rot) + anchor
    };

    Vector2 TRpnt{
        std::min(std::initializer_list<float>{crnrs[0].x, crnrs[1].x, crnrs[2].x, crnrs[3].x}),
        std::min(std::initializer_list<float>{crnrs[0].y, crnrs[1].y, crnrs[2].y, crnrs[3].y})
    };

    Vector2 BLpnt{
        std::max(std::initializer_list<float>{crnrs[0].x, crnrs[1].x, crnrs[2].x, crnrs[3].x}),
        std::max(std::initializer_list<float>{crnrs[0].y, crnrs[1].y, crnrs[2].y, crnrs[3].y})
    };

    return{
        TRpnt.x,
        TRpnt.y,
        BLpnt.x - TRpnt.x,
        BLpnt.y - TRpnt.y
    };
}
bool checkCollisionPointRotatedRec(Vector2 point, Rectangle rec, float rot, Vector2 anchor)
{
    Vector2 newPoint{floatAngleToVec2(vec2distance(point, anchor), vec2ToAngle(point - anchor) - rot) + anchor}; // counter rotate the point
    return CheckCollisionPointRec(newPoint, rec);
}
bool checkCollisionCircleRotatedRec(Vector2 pos, float rad, Rectangle rec, float rot, Vector2 anchor)
{
    Vector2 newPos{floatAngleToVec2(vec2distance(pos, anchor), vec2ToAngle(pos - anchor) - rot) + anchor};
    return CheckCollisionCircleRec(newPos, rad, rec);
}

Vector2 getScreenCenter()
{
    return getScreenSize()/2;
}