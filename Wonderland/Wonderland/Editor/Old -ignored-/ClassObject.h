////////////////////////////////////////////////////////////////////////////////
// Filename: ClassObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include "..\..\Support\Container\Array\Array.h"
#include "VariableObject.h"
#include "FunctionObject.h"

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
// Class name: ClassObject
////////////////////////////////////////////////////////////////////////////////
class ClassObject
{
//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ClassObject();
	~ClassObject();

//////////////////
// MAIN METHODS //
public: //////////

	// Add a new member variable
	VariableObject* AddMemberVariable(FluxType _variableType, std::string _variableName);

	// Add a new member function
	FunctionObject* AddMemberFunction(FluxType _returnType, std::string _functionName);

private:

	// Check if a variable with a given name exist
	bool MemberVariableExist(std::string _variableName);

	// Check if a function with a given name exist
	bool MemberFunctionExist(std::string _functionName);

///////////////
// VARIABLES //
private: //////

	// Conjunto de variáveis membros
	Array<VariableObject*> m_MemberVariableList;

	// Conjunto de funções membros
	Array<FunctionObject*> m_MemberFunctionList;
};
