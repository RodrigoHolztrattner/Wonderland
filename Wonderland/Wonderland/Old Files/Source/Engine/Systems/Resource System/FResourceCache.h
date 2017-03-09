////////////////////////////////////////////////////////////////////////////////
// Filename: FResourceCache.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FResourceCache_H_
#define _FResourceCache_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <unordered_map>
#include "Containers\Array\TArray.h"
#include "File\FFileIO.h"
#include "String\FHashedString.h"

/////////////
// DEFINES //
/////////////

/*

	=> The resource cache have references for all the loaded resources.

*/

// We know the IResource class
class IResource;

////////////////////////////////////////////////////////////////////////////////
// Class name: FResourceCache
////////////////////////////////////////////////////////////////////////////////
class FResourceCache
{
private:

public:

	FResourceCache();
	FResourceCache(const FResourceCache&);
	~FResourceCache();

	// Initialize the resource cache
	bool Initialize();

public:

	// Return a loaded resource
	IResource* GetLoadedResource(FHashedString _resourceName);

	// Insert a new loaded resource into the array
	void InsertLoadedResource(FHashedString _resourceName, IResource* _resource);

	// Update all resources (check their lifetime, call the update method, etc)
	void UpdateResources(float _time);

	// Return a reference to the resource array
	std::unordered_map<FHashedString, IResource*, FHashedString::Hasher, FHashedString::Equal>* GetResourcesReference()
	{
		return &m_MappedResources;
	}

private:

	// The unordered map that we will use to store the resources
	std::unordered_map<FHashedString, IResource*, FHashedString::Hasher, FHashedString::Equal> m_MappedResources;
};

#endif
