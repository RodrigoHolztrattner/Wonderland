////////////////////////////////////////////////////////////////////////////////
// Filename: UIBorderComponent.h
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
// Class name: UIBorderComponent
////////////////////////////////////////////////////////////////////////////////
class UIBorderComponent : public ECS_Component
{

//////////////////
// CONSTRUCTORS //
public: //////////

	UIBorderComponent();
	UIBorderComponent(const UIBorderComponent&);
	~UIBorderComponent();

private:

	// Add a unique ID to this component class
	AddComponentUniqueID(UIBorderComponent);

	// Register the class dependencies
	RegisterClassDependencies(UITreeComponent, UIFrameComponent, UIStateComponent);
 
///////////////
// MODIFIERS //
public: ///////

	// Set the border color
	void SetBorderColor(Vector4 _color);

	// Return the border color
	Vector4 GetBorderColor();

	// Set the border size
	void SetBorderSize(unsigned int _size);

	// Return the border size
	unsigned int GetBorderSize();

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

	// The border color
	Vector4 m_BorderColor;

	// The size
	unsigned int m_BorderSize;
};