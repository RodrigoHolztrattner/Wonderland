////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugReference.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "FluxPlugBase.h"

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
// Class name: FluxPlugReference
////////////////////////////////////////////////////////////////////////////////
class FluxPlugReference : public FluxPlugBase
{
/////////////
// DEFINES //
public: /////

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxPlugReference();
	FluxPlugReference(const FluxPlugReference& _other);
	~FluxPlugReference();

//////////////////
// MAIN METHODS //
public: //////////

	// Create/Initialize this object
	static FluxPlugReference* CreateVariableReference(FluxType _variableType, std::string _variableName = "");
	static FluxPlugReference* CreateExecReference(std::string _execName = "");

	// Set our variable type (if we are a variable reference)
	void SetVariableType(FluxType _type);

	// Return the variable type (if we are a variable reference)
	FluxType GetVariableType();

///////////////
// VARIABLES //
private: //////

	// If our type is a variable, we will use the variable type
	FluxType m_VariableType;

	// Default values ...
};
