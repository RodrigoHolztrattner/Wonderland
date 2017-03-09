////////////////////////////////////////////////////////////////////////////////
// Filename: VariableObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VariableObject.h"

VariableObject::VariableObject()
{
	// Set the initial data
	FluxType newType; newType.SetName("DummyType");
	m_Type = newType;
	m_Name = "DummyName";
}

VariableObject::VariableObject(const VariableObject& _other)
{
	// Copy the data
	m_Type = _other.m_Type;
	m_Name = _other.m_Name;
}

VariableObject::~VariableObject()
{
}

VariableObject* VariableObject::Create(FluxType _type, std::string _name)
{
	// Create the new variable
	VariableObject* newVariable = new VariableObject();

    // Set the data
	newVariable->m_Type = _type;
	newVariable->m_Name = _name;
    
    return newVariable;
}

std::string VariableObject::GetName()
{
	return m_Name;
}

void VariableObject::SetName(std::string _name)
{
	m_Name = _name;
}

FluxType VariableObject::GetType()
{
	return m_Type;
}

bool VariableObject::IsFromType(FluxType _type)
{
	if (!(m_Type.GetName().compare(_type.GetName())))
	{
		return true;
	}

	return false;
}