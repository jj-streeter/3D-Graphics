#ifndef VECTOR2_4620
#define VECTOR2_4620

#include <iostream>
#include <cmath>

struct Vector2
{
    float x, y;

    Vector2& operator+=(const Vector2& rhs);

    Vector2& operator-=(const Vector2& rhs);

    Vector2& operator*=(const float rhs);

    float length();

    Vector2 normalize();
};

Vector2 operator+(Vector2 lhs, const Vector2& rhs);

Vector2 operator-(Vector2 lhs, const Vector2& rhs);

Vector2 operator*(Vector2 lhs, const float rhs);

std::ostream& operator<<(std::ostream& os, const Vector2& v);

#endif