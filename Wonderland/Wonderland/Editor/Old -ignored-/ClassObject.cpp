////////////////////////////////////////////////////////////////////////////////
// Filename: ClassObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ClassObject.h"

ClassObject::ClassObject()
{
}

ClassObject::~ClassObject()
{
}

VariableObject* ClassObject::AddMemberVariable(FluxType _variableType, std::string _variableName)
{
	// Check if a member variable with the given name already exists
	if(MemberVariableExist(_variableName))
	{
		return nullptr;
	}

	// Create a new member variable object
	VariableObject* newVariable = new VariableObject;
	newVariable->Create(_variableType, _variableName);

	// Insert it into the array
	m_MemberVariableList.Add(newVariable);

	return newVariable;
}

FunctionObject* ClassObject::AddMemberFunction(FluxType _returnType, std::string _functionName)
{
	// Check if a member function with the given name already exists
	if(MemberFunctionExist(_functionName))
	{
		return nullptr;
	}

	// Create a new member function object
	FunctionObject* newFunction = new FunctionObject;
	newFunction->Create(_functionName);

	// Insert it into the array
	m_MemberFunctionList.Add(newFunction);

	return newFunction;
}

bool ClassObject::MemberVariableExist(std::string _variableName)
{
	return false;
}

bool ClassObject::MemberFunctionExist(std::string _functionName)
{
	return false;
}