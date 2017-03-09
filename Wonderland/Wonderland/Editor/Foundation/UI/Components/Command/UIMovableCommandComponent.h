////////////////////////////////////////////////////////////////////////////////
// Filename: UIMovableCommandComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"
#include "UICommandComponent.h"

#include "UICommandComponentCallback.h"

#include "..\..\..\..\Support\Math\Math.h"
#include "..\..\..\..\Support\Container\Array\StaticArray.h"
#include "..\..\ViewController\Modules\CommandModule\CommandType.h"

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
// Class name: UIMovableCommandComponent
////////////////////////////////////////////////////////////////////////////////
class UIMovableCommandComponent : public UICommandComponent
{
	// CommandModule is a friend class
	friend CommandModule;

//////////////////
// CONSTRUCTORS //
public: //////////

	UIMovableCommandComponent();
	UIMovableCommandComponent(const UIMovableCommandComponent&);
	~UIMovableCommandComponent();

///////////////
// MODIFIERS //
protected: ////

	// Process a given command
	virtual bool EvaluateCommand(CommandType _command);

/////////////
// VIRTUAL //
public: /////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed);

	// The clear method
	virtual void Clear();

//////////////
// CALLBACK //
public: //////

///////////////
// VARIABLES //
private: //////

	// The mouse relative press location
	Vector2 m_MouseRelativePressLocation;

	// If we are moving
	bool m_Moving;
};