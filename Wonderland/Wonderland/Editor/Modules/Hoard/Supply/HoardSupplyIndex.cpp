////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardSupplyIndex.h"

Hoard::Supply::HoardSupplyIndex::HoardSupplyIndex()
{
	// Set the initial data
	// ...
}

Hoard::Supply::HoardSupplyIndex::~HoardSupplyIndex()
{
}

void Hoard::Supply::HoardSupplyIndex::Create(HashedStringIdentifier _groupIdentifier, const char* _resourcePath)
{
	// Save the data
	m_Identifier = _groupIdentifier;
	m_ResourcePath.SetString(_resourcePath);
}