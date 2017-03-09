////////////////////////////////////////////////////////////////////////////////
// Filename: WTransform2D.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WTransform2D_H_
#define _WTransform2D_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Vector\Vector2.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: WTransform2D
////////////////////////////////////////////////////////////////////////////////
class WTransform2D
{
private:

public:
	WTransform2D();
	WTransform2D(const WTransform2D&);
	~WTransform2D();

	// Set the position
	void SetPosition(float _x, float _y);
	void SetPosition(Vector2 _position);

	// Set the size
	void SetSize(float _x, float _y);
	void SetSize(Vector2 _size);

	// Return the position / size
	Vector2 GetPosition();
	Vector2 GetSize();

	// Return true if the given point is inside this object
	bool IsPointInside(Vector2 _point);

protected:

	// The position
	Vector2 p_Position;

	// The size
	Vector2 p_Size;
};

//////////////
// TYPEDEFS //
//////////////

typedef WTransform2D WRect;
typedef WTransform2D WPoint;

#endif
