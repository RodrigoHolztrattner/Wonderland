////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuButton.h
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

// We know the UIMenuLaneView class
class UIMenuLaneView;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIMenuButton
////////////////////////////////////////////////////////////////////////////////
class UIMenuButton : public UIBase, public UIMenuChain
{
	// UIBase is a friend
	friend UIBase;

	// UIMenuLaneView is a friend
	friend UIMenuLaneView;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIMenuButton();

	// We cant copy or destruct too
	UIMenuButton(const UIMenuButton&);
	~UIMenuButton();

	// Create this widget (called from the UIBase)
	bool Create();

public:

	// Check if a given widget is related to this widget
	virtual bool IsRelated(UIMenuChain* _other, bool _ignoreChilds = false);

	// Create the lane view
	UIMenuLaneView* CreateLaneview();

	// Set if this is a top menu button
	void SetIsTopMenuButton();

	// Register the click callback
	void RegisterClickCallback(MemberCallback<void*> _callback);


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

	// The callback when we click on this button
	MemberCallback<void*> m_ClickCallback;

	// The lane view owner and child
	UIMenuLaneView* m_LaneViewChild;

	// If this is a top menu button
	bool m_IsTopMenuButton;

	// If we are pressing this button
	bool m_Pressing;

	// If this button was selected
	bool m_Selected;
};