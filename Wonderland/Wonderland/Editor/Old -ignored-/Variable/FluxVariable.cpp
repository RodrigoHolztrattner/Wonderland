////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxVariable.h"

FluxVariable::FluxVariable()
{
	// Set the initial data
	FluxType newType; newType.SetName("DummyType");
	m_Type = newType;
	m_Name = "DummyName";
}

FluxVariable::FluxVariable(const FluxVariable& _other)
{
	// Copy the data
	m_Type = _other.m_Type;
	m_Name = _other.m_Name;
}

FluxVariable::~FluxVariable()
{
}

FluxVariable* FluxVariable::Create(FluxType _type, std::string _name)
{
	// Create the new variable
	FluxVariable* newVariable = new FluxVariable();

    // Set the data
	newVariable->m_Type = _type;
	newVariable->m_Name = _name;
    
    return newVariable;
}

std::string FluxVariable::GetName()
{
	return m_Name;
}

void FluxVariable::SetName(std::string _name)
{
	m_Name = _name;
}

FluxType FluxVariable::GetType()
{
	return m_Type;
}

bool FluxVariable::IsFromType(FluxType _type)
{
	if (!(m_Type.GetName().compare(_type.GetName())))
	{
		return true;
	}

	return false;
}

bool FluxVariable::IsFromType(std::string _type)
{
	if (!(m_Type.GetName().compare(_type)))
	{
		return true;
	}

	return false;
}