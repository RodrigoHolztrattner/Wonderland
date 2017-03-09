////////////////////////////////////////////////////////////////////////////////
// Filename: FunctionLinker.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <string>
#include "..\Box.h"
#include "FunctionLinkerFlow.h"
#include "FunctionBody.h"

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
// Class name: FunctionLinker
////////////////////////////////////////////////////////////////////////////////
class FunctionLinker
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FunctionLinker(Flux::Box* _boxReference, Flux::FunctionBody* _functionBodyReference);
	~FunctionLinker();

//////////////////
// MAIN METHODS //
public: //////////

	// Create the linker flow
	bool CreateLinkerFlow();

	// Process the variable names
	bool ProcessVariableNames();

private:

	// Create the linker flow helper
	bool CreateLinkerFlowHelper(Flux::FunctionLinkerFlow* _currentLinkerFlow, Flux::FunctionFlow* _fromFunctionFlow);

	// Process the variable names helper
	bool ProcessVariableNamesHelper(Flux::FunctionLinkerFlow* _currentLinkerFlow);

	// Set a variable name from the given function flow variable data
	bool GetVariableNameFromFlowData(Flux::FunctionFlow* _currentFunctionFlow, Flux::FunctionFlow::FlowVariableObject* _flowVariableData, std::string& _variableName);

	// Find a linker flow by cross reference from a function flow
	Flux::FunctionLinkerFlow* FindLinkerFlowByCrossReference(Flux::FunctionFlow* _functionFlow);

///////////////
// VARIABLES //
private: //////

	// Our box reference handle
	Flux::Box*									m_BoxReference;

	// Our function body reference
	Flux::FunctionBody*							m_FunctionBodyReference;

	// Our variable name generator
	// ...

	// Our start and end flows
	Flux::FunctionLinkerFlow					m_StartLinkerFlow;
	Flux::FunctionLinkerFlow					m_EndLinkerFlow;

	// All linker flows
	std::vector<Flux::FunctionLinkerFlow*>		m_LinkerFlows;
};

// Flux workspace
NamespaceEnd(Flux)