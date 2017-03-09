////////////////////////////////////////////////////////////////////////////////
// Filename: UIFrameComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"
#include "UIFrameToken.h"
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

/** UITreeComponent */
class UITreeComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIFrameComponent
////////////////////////////////////////////////////////////////////////////////
class UIFrameComponent : public ECS_Component
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	UIFrameComponent();
	UIFrameComponent(const UIFrameComponent&);
	~UIFrameComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UIFrameComponent);
 
    // Register the class dependencies
    RegisterClassDependencies(UITreeComponent);	

///////////////
// MODIFIERS //
public: ///////

	// Set the frame data
	virtual void SetFrame(Vector2 _position, Vector2 _size);

	// Return the frame 
	virtual Vector4 GetFrame();

	// Return the frame position
	virtual Vector2 GetFramePosition();

	// Return the frame size
	virtual Vector2 GetFrameSize();

	// Return the frame end position
	virtual Vector2 GetFrameEndPosition();

	// Return true if a given point is inside this frame
	bool PointIsInsideFrame(Vector2 _point);

	// Return the screen frame
	Vector4 GetScreenFrame();

	// Return the current frame token
	UIFrameToken GetFrameToken();

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

	// The top left and bottom right points
	Vector2 m_TopLeft;
	Vector2 m_BottomRight;

	// The current frame token
	UIFrameToken m_FrameToken;
};