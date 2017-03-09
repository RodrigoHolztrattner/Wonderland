////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuLaneView.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIBase.h"

#include "..\..\ViewController\Modules\CommandModule\CommandType.h"
#include "..\..\..\..\Support\Callback\MemberCallback.h"
#include "UIMenuChain.h"
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

// We know the UIMenuButton
class UIMenuButton;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIMenuLaneView
////////////////////////////////////////////////////////////////////////////////
class UIMenuLaneView : public UIBase, public UIMenuChain
{
	// UIBase is a friend
	friend UIBase;

	// UIMenuButton is a friend
	friend UIMenuButton;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIMenuLaneView();

	// We cant copy or destruct too
	UIMenuLaneView(const UIMenuLaneView&);
	~UIMenuLaneView();

	// Create this widget (called from the UIBase)
	bool Create();

public:

	// Add a button to this menu
	UIMenuButton* AddButton(char* _label);

	// Check if a given widget is related to this widget
	virtual bool IsRelated(UIMenuChain* _other, bool _ignoreChilds = false);

/////////////
// VIRTUAL //
public: /////

	// Process a command (virtual, dont call the parent function back if overloaded)
	virtual bool ProcessCommand(CommandType* _command);

	// Render this widget
	virtual void Render() {};

	// Force visible
	virtual void ForceVisibleStatus(bool _status);

	// Confirm chain
	virtual void SetChainStatus(bool _status);

	// Echo the chain status
	virtual void EchoChainStatus(bool _status);

///////////////
// VARIABLES //
private: //////

	// The list of menu buttons
	Array<UIMenuButton*> m_MenuButtons;
};