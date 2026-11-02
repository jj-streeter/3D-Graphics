#ifndef VECTOR3_4620
#define VECTOR3_4620
/// in C++, every class gets its own file and previous header

#include <iostream>
#include <cmath>

/// classes are private, structs are public
struct Vector3
{
  float x, y, z;

  Vector3 &operator+=(const Vector3 &rhs);

  Vector3 &operator-=(const Vector3 &rhs);

  Vector3 &operator*=(const float rhs);

  float dot(const Vector3 &rhs);

  Vector3 cross(const Vector3 &rhs);

  float length();

  Vector3 normalize();
};

Vector3 operator+(Vector3 lhs, const Vector3 &rhs);

Vector3 operator-(Vector3 lhs, const Vector3 &rhs);

Vector3 operator*(Vector3 lhs, const float rhs);

std::ostream &operator<<(std::ostream &os, const Vector3 &v);

#endif