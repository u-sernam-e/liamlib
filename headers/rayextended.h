#ifndef RAYEXTENDED
#define RAYEXTENDED
#include "raylib.h"

Vector2 operator-(const Vector2& a);

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator/(const Vector2& a, const Vector2& b);

Vector2& operator+=(Vector2& a, const Vector2& b);
Vector2& operator-=(Vector2& a, const Vector2& b);
Vector2& operator*=(Vector2& a, const Vector2& b);
Vector2& operator/=(Vector2& a, const Vector2& b);

Vector2 operator+(const float& a, const Vector2& b);
Vector2 operator-(const float& a, const Vector2& b);
Vector2 operator*(const float& a, const Vector2& b);
Vector2 operator/(const float& a, const Vector2& b);

Vector2 operator+(const Vector2& a, const float& b);
Vector2 operator-(const Vector2& a, const float& b);
Vector2 operator*(const Vector2& a, const float& b);
Vector2 operator/(const Vector2& a, const float& b);

Vector2& operator+=(Vector2& a, const float& b);
Vector2& operator-=(Vector2& a, const float& b);
Vector2& operator*=(Vector2& a, const float& b);
Vector2& operator/=(Vector2& a, const float& b);

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);

Vector2 vecAbs(const Vector2& a);
float vec2distance(const Vector2& a, const Vector2& b);
float lowerLimitFrameTime(); // GetFrameTime(), but only goes down to 15 fps
float vec2ToFloat(Vector2 x);
float vec2ToAngle(Vector2 x);
Vector2 floatAngleToVec2(float x, float angle);

struct Circle
{
    Vector2 pos;
    float rad;
};

#endif