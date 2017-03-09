////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIBase.h"

#include "..\..\..\..\Support\Container\Array\Array.h"
#include "..\..\ViewController\Modules\CommandModule\CommandType.h"
#include "..\..\..\..\Support\Callback\MemberCallback.h"
#include "UIMenuButton.h"
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
// Class name: UIMenu
////////////////////////////////////////////////////////////////////////////////
class UIMenu : public UIBase
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIMenu();

	// We cant copy or destruct too
	UIMenu(const UIMenu&);
	~UIMenu();

	// Create this widget (called from the UIBase)
	virtual bool Create();

///////////////
// MODIFIERS //
public: ///////

	// Add a button to this menu
	UIMenuButton* AddButton(char* _label);

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

	// The list of menu buttons
	Array<UIMenuButton*> m_MenuButtons;

	// The callback when we click on this button
	MemberCallback<void*> m_ClickCallback;
};