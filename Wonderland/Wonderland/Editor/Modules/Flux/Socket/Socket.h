////////////////////////////////////////////////////////////////////////////////
// Filename: Socket.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\Handle\Handle.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Flux workspace
NamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: Socket
////////////////////////////////////////////////////////////////////////////////
class Socket : public Flux::Handle
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Socket();
	Socket(std::string _socketName); // Editor name
	~Socket();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
protected: ////

	// The socket editor name (visible name for the user)
	std::string m_EditorName;

	// If this socket is visible
	bool m_IsVisible;
};

// Flux workspace
NamespaceEnd(Flux)
