////////////////////////////////////////////////////////////////////////////////
// Filename: Vector3.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector3_H_
#define _Vector3_H_

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
class Vector4;

////////////////////////////////////////////////////////////////////////////////
// Class name: Vector3
////////////////////////////////////////////////////////////////////////////////
class Vector3
{
private:

public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(Vector2 _vector2);
	Vector3(Vector4 _vector4);
	Vector3(const Vector3& other);
	~Vector3();

	// Transform the position to screen position
	/* inline */ static Vector3 TransformToScreenPosition(Vector3 _position, Vector3 _size);

	// Transform the size to screen size
	/* inline */ static Vector3 TransformToScreenSize(Vector3 _size);

	Vector3 DivideBy(float _value)
	{
		Vector3 newVector;
		newVector.x = x / _value;
		newVector.y = y / _value;
		newVector.z = z / _value;

		return newVector;
	}

public:

	// Union with all types of values for this vector
	union
	{
		// For position, size, etc
		struct
		{
			float x, y, z;
		};

		// For color, pixel, etc
		struct
		{
			float a, b, c;
		};

		// Base
		float v[3];
	};
};

#endif
