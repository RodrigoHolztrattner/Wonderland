////////////////////////////////////////////////////////////////////////////////
// Filename: FunctionFlow.h
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

////////////////////////////////////////////////////////////////////////////////
// Class name: FunctionFlow
////////////////////////////////////////////////////////////////////////////////
class FunctionFlow
{
public:

	// The flow variable types
	enum class FlowVariableType
	{
		None,
		LocalVariable,
		MemberVariable,
		GlobalVariable,
		FunctionReturn
	};

	// The flow variable object
	struct FlowVariableObject
	{
		// The flow variable type
		FlowVariableType variableType;

		// The handle for the variable itself <LocalVariable, MemberVariable, GlobalVariable>
		Flux::Handle variableHandle;

		// The flow object to get the return value <FunctionReturn>
		unsigned int flowReturnId;
	};

	// The flow types
	enum class FlowType
	{
		Start,
		End,
		Normal
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FunctionFlow();
	~FunctionFlow();

//////////////////
// MAIN METHODS //
public: //////////

///////////////
// VARIABLES //
public: ///////

	// The flow id
	unsigned int										flowId;

	// The type of flow object (start, end, normal)
	FlowType											flowType;

	// The box reference handle
	Flux::Handle										boxReferenceHandle;

	// Input/output flow variables
	std::vector<FlowVariableObject>						flowInputVariables;
	std::vector<FlowVariableObject>						flowOutputVariables;

	// All the output flows
	std::vector<FunctionFlow*>							flowOutputs;
};

// Flux workspace
NamespaceEnd(Flux)