#pragma once
#pragma once
#include <cmath>
#include "Vec2.h"
#include "Vec3.h"

struct Mat3
{
	Vec3 c[3];
};

inline Mat3 identity()
{

	return
	Mat3
	{
		Vec3{ 1, 0, 0 },
		Vec3{ 0, 1, 0 },
		Vec3{ 0, 0, 1 }
	};
}


inline Mat3 transpose(const Mat3 &m)
{
	Mat3 t = m;
	t.c[0].y = m.c[1].x;
	t.c[0].z = m.c[2].x;
	t.c[1].z = m.c[2].y;
	t.c[1].x = m.c[0].y;
	t.c[2].x = m.c[0].z;
	t.c[2].y = m.c[1].z;
	return m;
}

inline Vec3 operator*(const Mat3 &m, const Vec3 &v)
{
	Mat3 t = transpose(m);
	Vec3 d;
	d.x = dot(t.c[0], v);
	d.y = dot(t.c[1], v);
	d.z = dot(t.c[2], v);
	return d;
}

inline Mat3 operator*(const Mat3 &a, const Mat3 &b)
{
	Mat3 t = transpose(a);
	Mat3 d;
	d.c[0] = { dot(t.c[0], b.c[0]), dot(t.c[0], b.c[1]), dot(t.c[0], b.c[2]) };
	d.c[1] = { dot(t.c[1], b.c[0]), dot(t.c[1], b.c[1]), dot(t.c[1], b.c[2]) };
	d.c[2] = { dot(t.c[2], b.c[0]), dot(t.c[2], b.c[1]), dot(t.c[2], b.c[2]) };
	return d;
}

inline Mat3 translate(float x, float y)
{
	Mat3 m;
	m.c[0] = { 1, 0, x };
	m.c[1] = { 0, 1, y };
	m.c[2] = { 0, 0, 1 };
	return m;
}

inline Mat3 rotate(float a)
{
	Mat3 m;
	m.c[0] = { cos(a),	-sin(a),	0 };
	m.c[1] = { sin(a),	cos(a),		0 };
	m.c[2] = { 0,		0,			1 };
	return m;
}

inline Mat3 scale(float w, float h)
{
	Mat3 m;
	m.c[0] = { w, 0, 0 };
	m.c[1] = { 0, h, 0 };
	m.c[2] = { 0, 0, 1 };
	return m;
}