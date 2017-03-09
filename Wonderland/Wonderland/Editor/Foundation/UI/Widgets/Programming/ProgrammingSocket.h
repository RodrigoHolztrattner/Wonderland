////////////////////////////////////////////////////////////////////////////////
// Filename: ProgrammingSocket.h
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

// We know the programing line object
class UIProgrammingLine;

////////////////////////////////////////////////////////////////////////////////
// Class name: ProgrammingSocket
////////////////////////////////////////////////////////////////////////////////
class ProgrammingSocket
{
public:

	// The socket type
	enum class Type
	{
		Flow,
		Data
	};

	// The behavior type
	enum class Behavior
	{
		In,
		Out
	};

	// The link type
	struct LinkType
	{
		// The socket linked
		ProgrammingSocket* socket;

		// The programming line that represents this link (UI)
		UIProgrammingLine* line;
	};

//////////////////////////////
// CONSTRUCTOR / DESTRUCTOR //
public: //////////////////////

	ProgrammingSocket();
	ProgrammingSocket(const ProgrammingSocket&);
	~ProgrammingSocket();

///////////////
// MODIFIERS //
public: ///////

	// Set the type
	void SetType(Type _type);

	// Set the behavior
	void SetBehavior(Behavior _behavior);

	// Return the type
	Type GetType();

	// Return the behavior
	Behavior GetBehavior();

protected:

	// Make a link with another programming socket
	bool MakeLink(ProgrammingSocket* _otherSocket, UIProgrammingLine* _line);



/////////////
// VIRTUAL //
public: /////

///////////////
// VARIABLES //
protected: ////

	// The socket type and behavior
	Type m_Type;
	Behavior m_Behavior;

	// And array of incomming links
	Array<LinkType> m_LinkArray;
};