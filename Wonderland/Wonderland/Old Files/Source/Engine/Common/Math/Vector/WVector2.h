////////////////////////////////////////////////////////////////////////////////
// Filename: WVector2.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WVector2_H_
#define _WVector2_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Primitive\WPrimitives.h"

/////////////
// DEFINES //
/////////////

// Pre declarations
class WVector3;
class WVector4;

////////////////////////////////////////////////////////////////////////////////
// Class name: WVector2
////////////////////////////////////////////////////////////////////////////////
class WVector2
{
private:

public:
	WVector2();
	WVector2(float _x, float _y);
	WVector2(WVector3 _vector3);
	WVector2(WVector4 _vector4);
	WVector2(const WVector2& other);
	~WVector2();

	// Calc a polar coordinate with offset
	static WVector2 PolarCoordinateWithOffset(WVector2 _current, float _direction, float _offset);

public:

	// Union with all types of values for this vector
	union
	{
		// For position, size, etc
		struct
		{
			Wfloat x, y;
		};

		// For color, pixel, etc
		struct
		{
			Wfloat a, b;
		};

		// Base
		Wfloat v[2];
	};
};

#endif
