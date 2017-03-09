////////////////////////////////////////////////////////////////////////////////
// Filename: UIMenuChain.h
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

// We know the UIMenuLaneView and UIMenuButton
class UIMenuLaneView;
class UIMenuButton;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIMenuChain
////////////////////////////////////////////////////////////////////////////////
class UIMenuChain
{
	// Friends
	friend UIMenuLaneView;
	friend UIMenuButton;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIMenuChain();

	// We cant copy or destruct too
	UIMenuChain(const UIMenuChain&);
	~UIMenuChain();

	// Register the chain owner
	void RegisterChainOwner(UIMenuChain* _chainOwner);

	// Force visible
	virtual void ForceVisibleStatus(bool _status);

	// Set the chain status
	virtual void SetChainStatus(bool _status);

	// Echo the chain status
	virtual void EchoChainStatus(bool _status);

	// Check if a given widget is related to this widget
	virtual bool IsRelated(UIMenuChain* _other, bool _ignoreChilds = false) = 0;

public:

/////////////
// VIRTUAL //
public: /////

///////////////
// VARIABLES //
protected: ////

	// The chain owner
	UIMenuChain* m_ChainOwner;
};