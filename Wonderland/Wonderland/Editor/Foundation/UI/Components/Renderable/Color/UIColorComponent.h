////////////////////////////////////////////////////////////////////////////////
// Filename: UIColorComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\ECS\ECS_Component.h"
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
// Class name: UIColorComponent
////////////////////////////////////////////////////////////////////////////////
class UIColorComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UIColorComponent();
	UIColorComponent(const UIColorComponent&);
	~UIColorComponent();

private:

	// Add a unique ID to this component class
	AddComponentUniqueID(UIColorComponent);

	// Register the class dependencies
	RegisterClassDependencies(UITreeComponent, UIFrameComponent, UIStateComponent);
 
///////////////
// MODIFIERS //
public: ///////

	// Set the color
	void SetColor(Vector4 _color);

	// Return the color
	Vector4 GetColor();

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

	// The color
	Vector4 m_Color;
};