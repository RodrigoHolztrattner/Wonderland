////////////////////////////////////////////////////////////////////////////////
// Filename: Variable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Variable.h"
#include "Type\TypeRegister.h"

Flux::Variable::Variable()
{
}

Flux::Variable::~Variable()
{
}

bool Flux::Variable::Build(Flux::Type* _Type, std::string _variableName)
{
	// Get the type register instance
	TypeRegister* typeRegisterInstance = TypeRegister::GetInstance();
	
	// Check if the type is valid
	if (!typeRegisterInstance->TypeWithNameExists(_Type->GetTypeName()))
	{
		return false;
	}

	// Set the type
	m_Type = _Type;

	// There is no need to check if the name is valid, the caller should test it //

	// Set the variable name
	m_VariableName = _variableName;

	// Set the booleans
	m_IsArray = false;
	m_IsPointer = false;

	return true;
}

std::string Flux::Variable::GetName()
{
	return m_VariableName;
}