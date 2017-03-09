////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceCache.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ResourceCache.h"

///////////////
// NAMESPACE //
///////////////

ResourceCache::ResourceCache()
{
	// Set the nulll ptr for the main ptr
	m_ResourceCacheData = nullptr;
}

ResourceCache::ResourceCache(const ResourceCache& other)
{
}

ResourceCache::~ResourceCache()
{
}

bool ResourceCache::Initialize(unsigned int _cacheSize, unsigned int _cacheAssociativity)
{
	// Set the variables
	m_CacheSize = _cacheSize;
	m_CacheAssociativity = _cacheAssociativity;

	// Allocate space for the cache data
	m_ResourceCacheData = new ResourceCacheData[m_CacheSize];

	// For each location
	for (int i = 0; i < m_CacheSize; i++)
	{
		// Allocate the associativity memory
		m_ResourceCacheData[i].resources = new Resource*[m_CacheAssociativity];

		// For each allocated ptr
		for (int j = 0; j < m_CacheAssociativity; j++)
		{
			// Set a null ptr
			m_ResourceCacheData[i].resources[j] = nullptr;
		}
	}

	return true;
}

Resource* ResourceCache::FindResource(FHashId _hashId)
{
	// Find the index
	unsigned int index = _hashId % m_CacheSize;

	// Get the resource data object
	ResourceCacheData* resourceDataObject = &m_ResourceCacheData[index];

	// For each possible location, compare the hashed name
	for (int i = 0; i < m_CacheAssociativity; i++)
	{
		// Check if this resource is valid
		if (resourceDataObject->resources[i] == nullptr) continue;

		// Compare the hashes
		if (resourceDataObject->resources[i]->GetHashId() == _hashId)
		{
			// We found the resource we are looking for
			Resource* resource = resourceDataObject->resources[i];

			// Set a null ptr for the resource location
			resourceDataObject->resources[i] = nullptr;

			return resource;
		}
	}

	// Resource not found!
	return nullptr;
}

void ResourceCache::AddResource(Resource* _resource)
{
	// Find the index
	unsigned int index = _resource->GetHashId() % m_CacheSize;

	// Get the resource data object
	ResourceCacheData* resourceDataObject = &m_ResourceCacheData[index];

	// For each possible location, try to find an empty one
	for (int i = 0; i < m_CacheAssociativity; i++)
	{
		// Check if this resource is valid
		if (resourceDataObject->resources[i] == nullptr)
		{
			// We found an empty location!
			resourceDataObject->resources[i] = _resource;

			return;
		}
	}

	// If we are here, there is no empty location, use a random one and discard the resource in that position
	int randomAssociativityIndex = rand() % m_CacheAssociativity;

	// Shutdown the resource at the random index location
	resourceDataObject->resources[randomAssociativityIndex]->Shutdown();

	// RE-USE the memory? //

	// Insert the current resource into that position
	resourceDataObject->resources[randomAssociativityIndex] = _resource;
}

void ResourceCache::Shutdown()
{
	// For each cache data
	for (int i = 0; i < m_CacheSize; i++)
	{
		// Get the resource data object
		ResourceCacheData* resourceDataObject = &m_ResourceCacheData[i];

		// For each position inside the data
		for (int resourceIndex = 0; resourceIndex < m_CacheAssociativity; resourceIndex++)
		{
			// Check if this resource location is empty
			if (resourceDataObject->resources[resourceIndex] != nullptr)
			{
				// Shutdown this resource
				resourceDataObject->resources[resourceIndex]->Shutdown();

				// RE-USE the memory? //
			}
		}

		// Delete the resource data object
		delete[] resourceDataObject;
	}

	// Delete the cache array
	delete[] m_ResourceCacheData;

	// Set the nulll ptr for the main ptr
	m_ResourceCacheData = nullptr;
}