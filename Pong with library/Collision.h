#pragma once
#include <math.h>
#include "Vec2.h"
#include "Vec3.h"
#include "sfwdraw.h"

float get2DAngle(const Vec2 &a, const Vec2 &b)
{
	Vec2 d = b - a;
	float angle = atan2f(d.y, d.x);
	return angle;
}

// add to Vector2 (a) to move it tward Vector2 (b)
Vec2 move(const Vec2 &a, const Vec2 &b)
{
	float d = get2DAngle(a, b);
	Vec2 m = { cos(d), sin(d) };
	return m;
}

float get3DAngle(const Vec3 &a, const Vec3 &b)
{
	float A = { a.x * b.x + a.y * b.y + a.z * b.z };
	float x = { sqrtf(a.x * a.x + a.y * a.y + a.z * a.z) };
	float y = { sqrtf(b.x * b.x + b.y * b.y + b.z * b.z) };
	float B = { x * y };
	float angle = { acosf(A / B) };
	return angle;
}

bool BoxCollision(const Vec2 &pos1, const Vec2 &dim1, const Vec2 &pos2, const Vec2 &dim2)
{
	if ((((pos1.x - dim1.x) <= (pos2.x + dim2.x)) && ((pos1.x + dim1.x) >= (pos2.x - dim2.x))) && (((pos1.y - dim1.y) <= (pos2.y + dim2.y)) && ((pos1.y + dim1.y) >= (pos2.y - dim2.y))))
	{
		return true;
	}
	else return false;
}

bool CircleCollision(const Vec2 &a, float r1, const Vec2 &b, float r2)
{
	Vec2 d = (b - a);
	float radii = r1 + r2;
	if (dot(d, d) <= (radii * radii))
	{
		return true;
	}
	else return false;
}