////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDynamicMemberFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "DynamicMemberFunction.h"

Flux::DynamicMemberFunction::DynamicMemberFunction()
{
	// Set the initial data
	// ...
}

Flux::DynamicMemberFunction::DynamicMemberFunction(std::string _name, Handle _classHandle) : Flux::Box(_name)
{
	// Set the initial data
	m_BondedClassHandle = _classHandle;
}

Flux::DynamicMemberFunction::~DynamicMemberFunction()
{
}

bool Flux::DynamicMemberFunction::AddLocalVariable(Flux::Variable _variable)
{
	// Check if the variable is valid
	// ...

	// Check if we can add this variable
	// ...

	// Add the variable
	m_LocalVariables.push_back(_variable);

	return true;
}

Flux::Handle Flux::DynamicMemberFunction::GetClassOwner()
{
	return m_BondedClassHandle;
}