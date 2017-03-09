////////////////////////////////////////////////////////////////////////////////
// Filename: UIButton.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIBase.h"

#include "..\..\ViewController\Modules\CommandModule\CommandType.h"
#include "..\..\..\..\Support\Callback\MemberCallback.h"
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
// Class name: UIButton
////////////////////////////////////////////////////////////////////////////////
class UIButton : public UIBase
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIButton();

	// We cant copy or destruct too
	UIButton(const UIButton&);
	~UIButton();

	// Create this widget (called from the UIBase)
	bool Create();

public:

	// Register the click callback
	void RegisterClickCallback(MemberCallback<void*> _callback);

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

	// The callback when we click on this button
	MemberCallback<void*> m_ClickCallback;

};