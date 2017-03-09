////////////////////////////////////////////////////////////////////////////////
// Filename: UITextField.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIBase.h"

#include "..\..\ViewController\Modules\CommandModule\CommandType.h"

#include <string>
#include <iostream>

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
// Class name: UITextField
////////////////////////////////////////////////////////////////////////////////
class UITextField : public UIBase
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UITextField();

	// We cant copy or destruct too
	UITextField(const UITextField&);
	~UITextField();

	// Create this widget (called from the UIBase)
	bool Create();

public:

	// Test
	void Update();

/////////////
// VIRTUAL //
public: /////

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Render this widget
	virtual void Render() {};

///////////////
// VARIABLES //
private: //////

};