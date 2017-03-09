////////////////////////////////////////////////////////////////////////////////
// Filename: UIProgrammingSocket.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\UIBase.h"
#include "ProgrammingSocket.h"

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

// 
class UIProgrammingLine;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIProgrammingSocket
////////////////////////////////////////////////////////////////////////////////
class UIProgrammingSocket : public UIBase, public ProgrammingSocket
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIProgrammingSocket();

	// We cant copy or destruct too
	UIProgrammingSocket(const UIProgrammingSocket&);
	~UIProgrammingSocket();

	// Create this widget (called from the UIBase)
	bool Create();

public:

protected:

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

	// The initial click
	Vector2 m_InitialClick;

	// The programming line and the programming socket links
	UIProgrammingLine* m_CurrentProgrammingLine;
};