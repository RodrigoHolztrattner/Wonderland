////////////////////////////////////////////////////////////////////////////////
// Filename: Vector4.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector4_H_
#define _Vector4_H_

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
class Vector2;
class Vector3;

////////////////////////////////////////////////////////////////////////////////
// Class name: Vector4
////////////////////////////////////////////////////////////////////////////////
class Vector4
{
private:

public:

	Vector4();
	Vector4(float _x, float _y, float _z, float _w);
	Vector4(Vector2 _vector2);
	Vector4(Vector2 _vectorA, Vector2 _vectorB);
	Vector4(Vector3 _vector3);
	Vector4(const Vector4& other);
	~Vector4();

	// Compare if two Vector4 are equal
	bool Compare(Vector4 _other)
	{
		if (_other.x != x || _other.y != y || _other.z != z || _other.w != w)
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
			Wfloat x, y, z, w;
		};

		// For color, pixel, etc
		struct
		{
			Wfloat a, b, c, d;
		};

		// For frame
		struct
		{
			float x, y, width, height;
		};

		// Base
		float v[4];
	};

};

#endif
