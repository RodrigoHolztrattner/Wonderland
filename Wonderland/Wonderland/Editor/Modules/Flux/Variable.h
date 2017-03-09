////////////////////////////////////////////////////////////////////////////////
// Filename: Variable.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "Handle\Handle.h"
#include "Type\Type.h"
#include <string>

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
// Class name: Variable
////////////////////////////////////////////////////////////////////////////////
class Variable : public Handle
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Variable();
	~Variable();
	
	// Build the variable
	bool Build(Flux::Type* _Type, std::string _variableName);

	// Return the variable name
	std::string GetName();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
private: //////

	// The variable type
	Flux::Type* m_Type;

	// The variable name
	std::string m_VariableName;

	// If this type is an array
	bool m_IsArray;

	// If this type should be treated like a pointer
	bool m_IsPointer;
};

typedef Variable MemberVariable;

// Flux workspace
NamespaceEnd(Flux)