////////////////////////////////////////////////////////////////////////////////
// Filename: FunctionLinkerFlow.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\..\Handle\Handle.h"

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

// We know the FunctionFlow class
class FunctionFlow;

////////////////////////////////////////////////////////////////////////////////
// Class name: FunctionLinkerFlow
////////////////////////////////////////////////////////////////////////////////
class FunctionLinkerFlow
{
public:

	// The linker variable
	struct LinkerVariableObject
	{
		// The variable name
		std::string variableName;
	};

	// The flow types
	enum class LinkerFlowType
	{
		Start,
		End,
		Normal
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FunctionLinkerFlow();
	~FunctionLinkerFlow();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
public: ///////

	// The function flow id we use for reference
	unsigned int											functionFlowIdReference;

	// Our function flow reference
	Flux::FunctionFlow*										functionFlowReference;

	// The type of flow object (start, end, normal)
	// LinkerFlowType											flowType;

	// Input/output flow variables
	std::vector<LinkerVariableObject>						flowInputVariables;
	std::vector<LinkerVariableObject>						flowOutputVariables;

	// All the output flows
	std::vector<FunctionLinkerFlow*>						flowOutputs;
};

// Flux workspace
NamespaceEnd(Flux)