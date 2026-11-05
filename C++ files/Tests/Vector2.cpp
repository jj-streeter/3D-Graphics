#include "Vector2.hpp"

Vector2& Vector2::operator+=(const Vector2& rhs){
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs){
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(const float rhs){
    x *= rhs;
    y *= rhs;
    return *this;
}

float Vector2::length(){
    return sqrt(x * x + y * y);
}

Vector2 Vector2::normalize(){
    float l = length();
    if (l == 0) return Vector2{0, 0};
    return Vector2{x / l, y / l};
}

Vector2 operator+(Vector2 lhs, const Vector2& rhs){
    return lhs += rhs;
}

Vector2 operator-(Vector2 lhs, const Vector2& rhs){
    return lhs -= rhs;
}

Vector2 operator*(Vector2 lhs, const float rhs){
    return lhs *= rhs;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}