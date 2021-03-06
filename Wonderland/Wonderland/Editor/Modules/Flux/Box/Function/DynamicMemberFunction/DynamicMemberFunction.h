////////////////////////////////////////////////////////////////////////////////
// Filename: DynamicMemberFunction.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "..\..\Box.h"
#include "..\..\..\Variable.h"

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
// Class name: DynamicMemberFunction
////////////////////////////////////////////////////////////////////////////////
class DynamicMemberFunction : public Flux::Box
{

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	DynamicMemberFunction();
	DynamicMemberFunction(std::string _name, Handle _classHandle);
	~DynamicMemberFunction();

//////////////////
// MAIN METHODS //
public: //////////

	// Add a local variable
	bool AddLocalVariable(Flux::Variable _variable);

	// Return the class owner handle
	Flux::Handle GetClassOwner();

///////////////
// VARIABLES //
private: //////

	// The local variables
	std::vector<Flux::Variable> m_LocalVariables;

	// The bounded class
	Flux::Handle m_BondedClassHandle;
};

// Flux workspace
NamespaceEnd(Flux)