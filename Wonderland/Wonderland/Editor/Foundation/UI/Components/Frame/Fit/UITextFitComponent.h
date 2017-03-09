////////////////////////////////////////////////////////////////////////////////
// Filename: UITextFitComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\ECS\ECS_Component.h"
#include "..\..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\..\Support\Container\Array\Array.h"
#include "..\UIFrameToken.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/** UIFrameComponent */
class UIFrameComponent;

/** UITextComponent */
class UITextComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: UITextFitComponent
////////////////////////////////////////////////////////////////////////////////
class UITextFitComponent : public ECS_Component
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	UITextFitComponent();
	UITextFitComponent(const UITextFitComponent&);
	~UITextFitComponent();

private:

	// Add a unique ID to this component class
	AddComponentUniqueID(UITextFitComponent);

	// Register the class dependencies
	RegisterClassDependencies(UIFrameComponent, UITextComponent);

///////////////
// MODIFIERS //
public: ///////

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
protected: ////

	// The last text size
	Vector2 m_LastTextSize;

};