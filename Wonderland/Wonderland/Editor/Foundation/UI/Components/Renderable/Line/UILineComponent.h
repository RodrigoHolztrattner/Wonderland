////////////////////////////////////////////////////////////////////////////////
// Filename: UILineComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIRenderableComponent.h"
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"

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

/** UIFrameComponent */
class UIFrameComponent;

/** UIFrameComponent */
class UIStateComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UILineComponent
////////////////////////////////////////////////////////////////////////////////
class UILineComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UILineComponent();
	UILineComponent(const UILineComponent&);
	~UILineComponent();

private:

	// Add a unique ID to this component class
	AddComponentUniqueID(UILineComponent);

	// Register the class dependencies
	RegisterClassDependencies(UITreeComponent, UIFrameComponent, UIStateComponent);
 
///////////////
// MODIFIERS //
public: ///////

	// Set the line color
	void SetLineColor(Vector4 _color);

	// Return the line color
	Vector4 GetLineColor();

	// Set the line size
	void SetLineSize(unsigned int _size);

	// Return the line size
	unsigned int GetLineSize();

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

//////////////
// CALLBACK //
private: /////

///////////////
// VARIABLES //
private: /////

	// The line color
	Vector4 m_LineColor;

	// The size
	unsigned int m_LineSize;
};