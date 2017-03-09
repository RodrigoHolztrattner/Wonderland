////////////////////////////////////////////////////////////////////////////////
// Filename: UICommandComponent.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\..\ECS\ECS_Component.h"

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

/** UITreeComponent */
class UITreeComponent;

/** UIFrameComponent */
class UIFrameComponent;

/** UIFrameComponent */
class UIStateComponent;

/** CommandModule */
class CommandModule;

////////////////////////////////////////////////////////////////////////////////
// Class name: UICommandComponent
////////////////////////////////////////////////////////////////////////////////
class UICommandComponent : public ECS_Component
{
	// CommandModule is a friend class
	friend CommandModule;

//////////////////
// CONSTRUCTORS //
public: //////////

	UICommandComponent();
	UICommandComponent(const UICommandComponent&);
	~UICommandComponent();

private:
 
    // Add a unique ID to this component class
    AddComponentUniqueID(UICommandComponent);
 
    // Register the class dependencies
    RegisterClassDependencies(UITreeComponent, UIFrameComponent, UIStateComponent);	

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

	// Set the command callback
	void SetCommandCallback(UICommandComponentCallback<CommandType*> _callback);

///////////////
// VARIABLES //
private: //////

	// The component on focus
	UICommandComponent* m_ComponentOnFocus;

	// The command callback
	UICommandComponentCallback<CommandType*> m_CommandCallback;

};