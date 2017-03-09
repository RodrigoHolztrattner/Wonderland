////////////////////////////////////////////////////////////////////////////////
// Filename: FluxPlugReference.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxPlugReference.h"

FluxPlugReference::FluxPlugReference()
{
	// Set the initial data
	// ...
}

FluxPlugReference::FluxPlugReference(const FluxPlugReference& _other)
{
	// Copy the plug type and name
	m_VariableType = _other.m_VariableType;
}

FluxPlugReference::~FluxPlugReference()
{
}

FluxPlugReference* FluxPlugReference::CreateVariableReference(FluxType _variableType, std::string _variableName)
{
	// Create the plug reference
	FluxPlugReference* newReference = new FluxPlugReference();

	// Set the data
	newReference->SetPlugType(PlugType::Variable);
	newReference->SetPlugName(_variableName);
	newReference->m_VariableType = _variableType;

	return newReference;
}

FluxPlugReference* FluxPlugReference::CreateExecReference(std::string _execName)
{
	// Create the plug reference
	FluxPlugReference* newReference = new FluxPlugReference();

	// Set the data
	newReference->SetPlugType(PlugType::ExecLink);
	newReference->SetPlugName(_execName);

	return newReference;
}

void FluxPlugReference::SetVariableType(FluxType _type)
{
	m_VariableType = _type;
}

FluxType FluxPlugReference::GetVariableType()
{
	return m_VariableType;
}