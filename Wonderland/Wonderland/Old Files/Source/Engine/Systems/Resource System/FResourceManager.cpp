///////////////////////////////////////////////////////////////////////////////
// Filename: FResourceManager.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FResourceManager.h"
#include "IResource.h"

FResourceManager::FResourceManager()
{
}

FResourceManager::FResourceManager(const FResourceManager& other)
{
}

FResourceManager::~FResourceManager()
{
}

bool FResourceManager::Initialize(const char* _mainResourceHeader)
{
	/*
	
		=> Load the main data resource

	*/

	return true;
}

FResourceManager::ResourceHeader* FResourceManager::GetResourceHeader(FHashedString _resourceName)
{
	// LOCK // ???

	// Try to find the resource
	std::unordered_map<size_t, ResourceHeader>::iterator resource = m_ResourceHeaders.find(_resourceName.Hash());

	// Check if we found it
	if (resource != m_ResourceHeaders.end())
	{
		// Return the resource header 
		return &(*resource).second;
	}

	// Return a null ptr -header-
	return nullptr;
}

////////////
// GLOBAL //
////////////
