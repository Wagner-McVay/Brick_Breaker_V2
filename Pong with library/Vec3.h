#pragma once
#include <cmath>

struct Vec3
{
	float x, y, z;
};

/*
Vector Addition, Subtraction
Scalar Multiplication, Division
Unary Inverse
Dot Product (Scalar Projection)
Magnitude
Normal
*/

// function definitions in headers must be inlined!

inline Vec3 operator+(const Vec3 &a, const Vec3 &b)
{
	return Vec3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
	return Vec3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vec3 operator*(const Vec3 &a, float b)
{
	return Vec3{ a.x * b, a.y * b, a.z * b };
}

inline Vec3 operator/(const Vec3 &a, float b)
{
	return Vec3{ a.x / b, a.y / b, a.z / b };
}

// Vector3 (a) times -1
inline Vec3 operator-(const Vec3 &a)
{
	return a*-1;
}

// sum of Vector3 (a) times Vector3 (b)
inline float dot(const Vec3 &a, const Vec3 &b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

// magnitude from (0,0) to Vector3 (a)
inline float magnitude(const Vec3 &a)
{
	return sqrt(dot(a, a));
}

// magnitude from Vector3 (a) to Vector3 (b)
inline float magnitude2(const Vec3 &a, const Vec3 &b)
{
	return sqrt(dot(b - a, b - a));
}

// position of Vector3 one unit of magnitude from (0,0) to Vector3 (a)
inline Vec3 normal(const Vec3 &a)
{
	return a / magnitude(a);
}

// position of Vector3 one unit of magnitude from (const Vector3 &b) to (const Vector3 &a)
inline Vec3 normal2(const Vec3 &a, const Vec3 &b)
{
	return b - a / magnitude2(a, b);
}