////////////////////////////////////////////////////////////////////////////////
// Filename: VariableNameProvider.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VariableNameProvider.h"

VariableNameProvider::VariableNameProvider()
{
    // Set the initial data
	m_InternalCounter = 0;
}

VariableNameProvider::~VariableNameProvider()
{
}

std::string VariableNameProvider::GetValidVariableName()
{
	std::string variableName = "val" + std::to_string(m_InternalCounter);
	m_InternalCounter++;
	return variableName;
}