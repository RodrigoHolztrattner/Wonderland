////////////////////////////////////////////////////////////////////////////////
// Filename: UIProgrammingLine.h
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

// We know the UIProgrammingSocket
class UIProgrammingSocket;

////////////////////////////////////////////////////////////////////////////////
// Class name: UIProgrammingLine
////////////////////////////////////////////////////////////////////////////////
class UIProgrammingLine : public UIBase
{
	// UIBase is a friend
	friend UIBase;

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
protected: ///////////////////

	// We cant create this widget without using the UIBase::Create()
	UIProgrammingLine();

	// We cant copy or destruct too
	UIProgrammingLine(const UIProgrammingLine&);
	~UIProgrammingLine();

	// Create this widget (called from the UIBase)
	bool Create();

public:

	// Set the sockets
	void SetSockets(UIProgrammingSocket* _from, UIProgrammingSocket* _to);

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

	// The sockets
	UIProgrammingSocket* m_StartSocket;
	UIProgrammingSocket* m_EndSocket;

	// The socket frame object (to check if one of them changed)
	Vector4 m_StartSocketFrame;
	Vector4 m_EndSocketFrame;
};