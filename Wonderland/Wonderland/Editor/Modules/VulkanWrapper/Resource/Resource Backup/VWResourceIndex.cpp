////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceIndex.h"
#include "..\VWContext.h"

VulkanWrapper::VWResourceIndex::VWResourceIndex()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWResourceIndex::~VWResourceIndex()
{
}

void VulkanWrapper::VWResourceIndex::Create(HashedStringIdentifier _groupIdentifier, const char* _resourcePath)
{
	// Save the data
	m_Identifier = _groupIdentifier;
	m_ResourcePath.SetString(_resourcePath);
}