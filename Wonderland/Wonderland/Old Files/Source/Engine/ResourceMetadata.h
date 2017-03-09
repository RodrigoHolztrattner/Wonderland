////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceMetadata.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <map>

#include "ResourceDefinitions.h"
#include "Common\String\FHashedString.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: ResourceMetadata
////////////////////////////////////////////////////////////////////////////////
class ResourceMetadata
{

public:
	ResourceMetadata();
	ResourceMetadata(const ResourceMetadata&);
	~ResourceMetadata();

	// Initialize the resource metadata
	bool Initialize();

	// Return the resource metadata
	ResourceDefinitions::ResourceHeader* GetResourceMetadata(unsigned int _resourceIndex)
	{
		return &m_ResourceMetadata[_resourceIndex];
	}

	// Return a resource index
	unsigned int GetResourceIndex(FHashId _hashId)
	{
		// Find the value
		std::map<FHashId, unsigned int>::iterator it = m_ResourceMetadataIndex.find(_hashId);
		if (it != m_ResourceMetadataIndex.end())
		{
			// Return the metadata
			return it->second;
		}

		// No metadata found!
		return -1;
	}

	// Return the total number of resources
	unsigned int GetNumberResources()
	{
		return m_NumberResources;
	}

	// Return the total number of files
	unsigned int GetNumberFiles()
	{
		return m_NumberFiles;
	}

private:

	// The total number of resources
	unsigned int m_NumberResources;

	// The number of files we are using
	unsigned int m_NumberFiles;

	// The resource metadata
	std::vector<ResourceDefinitions::ResourceHeader> m_ResourceMetadata;

	// The resource metadata index (ordered by hashId)
	std::map<FHashId, unsigned int> m_ResourceMetadataIndex;
};
