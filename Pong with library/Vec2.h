#pragma once
#include <cmath>

struct Vec2
{
	float x, y;
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

inline Vec2 operator+(const Vec2 &a, const Vec2 &b)
{
	return Vec2{ a.x + b.x, a.y + b.y };
}

inline Vec2 operator-(const Vec2 &a, const Vec2 &b)
{
	return Vec2{ a.x - b.x, a.y - b.y };
}

inline Vec2 operator*(const Vec2 &a, float b)
{
	return Vec2{ a.x * b, a.y * b };
}

inline Vec2 operator/(const Vec2 &a, float b)
{
	return Vec2{ a.x / b, a.y / b };
}

// Vector2 (a) times -1
inline Vec2 operator-(const Vec2 &a)
{
	return a*-1;
}

// sum of Vector2 (a) times Vector2 (b)
inline float dot(const Vec2 &a, const Vec2 &b)
{
	return a.x*b.x + a.y*b.y;
}

// magnitude from (0,0) to Vector2 (a)
inline float magnitude(const Vec2 &a)
{
	return sqrt(dot(a, a));
}

// magnitude from Vector2 (a) to Vector2 (b)
inline float magnitude2(const Vec2 &a, const Vec2 &b)
{
	return magnitude(b - a);
}

// position of Vector2 one unit of magnitude from (0,0) to Vector2 (a)
inline Vec2 normal(const Vec2 &a)
{
	return a / magnitude(a);
}

// position of Vector2 one unit of magnitude from Vector2 (b) to Vector2 (a)
inline Vec2 normal2(const Vec2 &a, const Vec2 &b)
{
	return b - a / magnitude2(a, b);
}