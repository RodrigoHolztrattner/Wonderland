////////////////////////////////////////////////////////////////////////////////
// Filename: Vector2.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector2_H_
#define _Vector2_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Primitive\Primitives.h"

/////////////
// DEFINES //
/////////////

// Pre declarations
class Vector3;
class Vector4;

////////////////////////////////////////////////////////////////////////////////
// Class name: Vector2
////////////////////////////////////////////////////////////////////////////////
class Vector2
{
private:

public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(Vector3 _vector3);
	Vector2(Vector4 _vector4);
	Vector2(const Vector2& other);
	~Vector2();

	// Calc a polar coordinate with offset
	static Vector2 PolarCoordinateWithOffset(Vector2 _current, float _direction, float _offset);

	// Clamp the vector value
	static Vector2 Clamp(Vector2 _val, Vector2 _min, Vector2 _max);

	Vector2 DivideBy(float _value)
	{
		Vector2 newVector;
		newVector.x = x / _value;
		newVector.y = y / _value;

		return newVector;
	}

	Vector2 DivideBy(float _value1, float _value2)
	{
		Vector2 newVector;
		newVector.x = x / _value1;
		newVector.y = y / _value2;

		return newVector;
	}

	// Compare if two Vector2 are equal
	bool Compare(Vector2 _other)
	{
		if (_other.x != x || _other.y != y)
		{
			return false;
		}

		return true;
	}

public:

	// Union with all types of values for this vector
	union
	{
		// For position, size, etc
		struct
		{
			float x, y;
		};

		// For color, pixel, etc
		struct
		{
			float a, b;
		};

		// For size
		struct
		{
			float width, height;
		};

		// Base
		float v[2];
	};
};

#endif
