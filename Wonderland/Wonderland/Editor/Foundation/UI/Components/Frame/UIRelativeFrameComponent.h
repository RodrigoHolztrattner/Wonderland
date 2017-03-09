////////////////////////////////////////////////////////////////////////////////
// Filename: UIRelativeFrameComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIFrameComponent.h"
#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\Array.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UIRelativeFrameComponent
////////////////////////////////////////////////////////////////////////////////
class UIRelativeFrameComponent : public UIFrameComponent
{
//////////
// ENUM //
public: //

	// The restriction enum
	enum Restriction
	{
		None	= 0,
		X		= 1 << 0,
		Y		= 1 << 1,
		Width	= 1 << 2,
		Height	= 1 << 3
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	UIRelativeFrameComponent();
	UIRelativeFrameComponent(const UIRelativeFrameComponent&);
	~UIRelativeFrameComponent();

private:
 
///////////////
// MODIFIERS //
public: ///////

	// Set the frame data
	void SetFrame(Vector2 _position, Vector2 _size, int _restriction = Restriction::None);

	/*
	// Return the frame position
	Vector2 GetFramePosition();

	// Return the frame size
	Vector2 GetFrameSize();

	// Return the frame end position
	Vector2 GetFrameEndPosition();
	*/

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

	// Called by the parent when he changed his frame
	virtual void ParentChagedFrame();

//////////////
// CALLBACK //
private: /////

	// Frame has changed callback
	// ...

///////////////
// VARIABLES //
protected: ////

	// The top left and bottom right relative points
	Vector2 m_TopLeftRelative;
	Vector2 m_BottomRightRelative;

	// The restriction
	int m_Restriction;
};