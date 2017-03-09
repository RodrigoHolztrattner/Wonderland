////////////////////////////////////////////////////////////////////////////////
// Filename: Math.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Math_H_
#define _Math_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <stdlib.h>
#include <math.h>
#include <algorithm>

// Base primitives
#include "Primitive\Primitives.h"

// Vectors
#include "Vector\Vector2.h"
#include "Vector\Vector3.h"
#include "Vector\Vector4.h"

// Quaternion
#include "Quaternion\WQuaternion.h"

// Matrices
#include "Matrix\WMatrix4.h"

//

// Transform 2D and 3D
#include "Transform\WTransform2D.h"
#include "Transform\WTransform3D.h"

/*
static float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

template <typename T1, typename T2>
static T1 Lerp(T1 _a, T2 _b, float _interval)
{
	return _a + (_b - _a) * _interval;
}
*/

static bool RectangleIntersectsSphere(Vector2 Bmin, Vector2 Bmax, Vector2 C, float r) 
{
	float r2 = r * r;
	float dmin = 0;

	// x
	if (C.x < Bmin.x)
	{
		dmin += sqrt(C.x - Bmin.x);
	}
	else if (C.x > Bmax.x)
	{
		dmin += sqrt(C.x - Bmax.x);
	}

	// y
	if (C.y < Bmin.y)
	{
		dmin += sqrt(C.y - Bmin.y);
	}
	else if (C.y > Bmax.y)
	{
		dmin += sqrt(C.y - Bmax.y);
	}

	return dmin <= r2;
}

static float Distance(Vector2 _from, Vector2 _to)
{
	return sqrt((_to.x - _from.x) * (_to.x - _from.x) + (_to.y - _from.y) * (_to.y - _from.y));
}

static bool SquareCollision(Vector2 _squareOneOrigin, Vector2 _squareOneSize, Vector2 _squareTwoOrigin, Vector2 _squareTwoSize)
{
	// AABB 1
	float x1Min = _squareOneOrigin.x;
	float x1Max = _squareOneOrigin.x + _squareOneSize.x;
	float y1Max = _squareOneOrigin.y + _squareOneSize.y;
	float y1Min = _squareOneOrigin.y;

	// AABB 2
	float x2Min = _squareTwoOrigin.x;
	float x2Max = _squareTwoOrigin.x + _squareTwoSize.x;
	float y2Max = _squareTwoOrigin.y + _squareTwoSize.y;
	float y2Min = _squareTwoOrigin.y;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	return true;
}

static float Clamp(float _value, float _min, float _max)
{
	if (_value > _max)
	{
		return _max;
	}
	if (_value < _min)
	{
		return _min;
	}
	return _value;
}

#endif
