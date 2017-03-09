////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceCache.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <cstdlib>
#include <cstring>

#include "Resource.h"
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
// Class name: ResourceCache
////////////////////////////////////////////////////////////////////////////////
class ResourceCache
{
	struct ResourceCacheData
	{
		// The resources (associativity = size)
		Resource** resources;
	};

public:
	ResourceCache();
	ResourceCache(const ResourceCache&);
	~ResourceCache();

	// Initialize the resource cache
	bool Initialize(unsigned int _cacheSize, unsigned int _cacheAssociativity);

	// Try to find a resource
	Resource* FindResource(FHashId _hashId);

	// Insert a resource into the cache
	void AddResource(Resource* _resource);

	// Shutdown the resource cache
	void Shutdown();

private:

	// The cache size and associativity
	unsigned int m_CacheSize;
	unsigned int m_CacheAssociativity;

	// The cache data (cache size = size)
	ResourceCacheData* m_ResourceCacheData;
};