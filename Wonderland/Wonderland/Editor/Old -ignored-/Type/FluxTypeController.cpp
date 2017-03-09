////////////////////////////////////////////////////////////////////////////////
// Filename: FluxTypeController.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxTypeController.h"

FluxTypeController::FluxTypeController()
{
    // Set the initial data
	// ...
}

FluxTypeController::~FluxTypeController()
{
}

void FluxTypeController::AddType(std::string _typeName, FluxType::TypeOrigin _origin)
{
	// Create the new type
	FluxType newType;

	// Set the type data
	newType.CreateType(_typeName, _origin);

	// Add it to the map
	m_TypeMap[_typeName] = newType;
}

void FluxTypeController::RemoveType(FluxType _type)
{
	// Try to find the type
	std::unordered_map<std::string, FluxType>::const_iterator got = m_TypeMap.find(_type.GetName());
	if (got != m_TypeMap.end())
	{
		// Remove the type
		m_TypeMap.erase(got);
	}
}

bool FluxTypeController::ValidateType(FluxType _type)
{
	// Try to find the type
	std::unordered_map<std::string, FluxType>::const_iterator got = m_TypeMap.find(_type.GetName());
	if (got == m_TypeMap.end())
	{
		return false;
	}

	return true;
}

FluxType FluxTypeController::GetTypeByName(std::string _typeName)
{
	// Try to find the type
	std::unordered_map<std::string, FluxType>::const_iterator got = m_TypeMap.find(_typeName);
	if (got != m_TypeMap.end())
	{
		// Return the type
		return got->second;
	}

	FluxType nullType; nullType.CreateType(""); // Problem!
	return nullType;
}