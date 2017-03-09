////////////////////////////////////////////////////////////////////////////////
// Filename: Class.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Class.h"
#include "..\Type\Type.h"

Flux::Class::Class()
{
}

Flux::Class::Class(std::string _className) : m_ClassName(_className)
{
}

Flux::Class::~Class()
{
}

void Flux::Class::SetClassName(std::string _name)
{
	// Set the name
	m_ClassName = _name;

	// Echo the change
	// ...
}

std::string Flux::Class::GetClassName()
{
	return m_ClassName;
}

bool Flux::Class::AddMemberVariable(Flux::MemberVariable _memberVariable)
{
	// Check if we can add this variable
	// ...

	// Add the new variable
	m_MemberVariables.push_back(_memberVariable);

	return true;
}

bool Flux::Class::AddMemberFunction(Flux::DynamicMemberFunction _memberFunction)
{
	// Check if we can add this variable
	// ...

	// Add the member function
	m_MemberFunctions.push_back(_memberFunction);

	return true;
}

Flux::DynamicMemberFunction* Flux::Class::GetMemberFunction(Flux::Handle _memberHandle)
{
	// For each member function
	for (int i = 0; i < m_MemberFunctions.size(); i++)
	{
		// Get the member function
		Flux::DynamicMemberFunction* memberFunction = &m_MemberFunctions[i];

		// Compare the handle
		if (memberFunction->CompareHandle(_memberHandle))
		{
			return memberFunction;
		}
	}

	return nullptr;
}

Flux::DynamicMemberFunction* Flux::Class::GetMemberFunction(std::string _memberName)
{
	// For each member function
	for (int i = 0; i < m_MemberFunctions.size(); i++)
	{
		// Get the member function
		Flux::DynamicMemberFunction* memberFunction = &m_MemberFunctions[i];

		// Compare the names
		if (!memberFunction->GetName().compare(_memberName))
		{
			return memberFunction;
		}
	}

	return nullptr;
}

Flux::MemberVariable* Flux::Class::GetMemberVariable(Flux::Handle _memberHandle)
{
	// For each member variable
	for (int i = 0; i < m_MemberVariables.size(); i++)
	{
		// Get the member variable
		Flux::MemberVariable* memberVariable = &m_MemberVariables[i];

		// Compare the handle
		if (memberVariable->CompareHandle(_memberHandle))
		{
			return memberVariable;
		}
	}

	return nullptr;
}