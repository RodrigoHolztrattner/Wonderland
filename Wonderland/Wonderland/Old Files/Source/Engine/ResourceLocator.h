////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceLocator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "ResourceDefinitions.h"
#include "ResourceMetadata.h"
#include "ResourceCache.h"
#include "Resource.h"

#include "Common\Containers\Pointer\IndirectionPointer.h"

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
// Class name: ResourceLocator
////////////////////////////////////////////////////////////////////////////////
class ResourceLocator
{
	// The resource locator data
	struct ResourceLocatorData
	{
		// The resource itself
		IndirectionPointer<Resource>* resource;

		// The allocation method
		Resource*(*createResourceFunctor)();
	};

public:
	ResourceLocator();
	ResourceLocator(const ResourceLocator&);
	~ResourceLocator();

	// Initialize the resource locator
	bool Initialize(unsigned int _numberResources);

	// Get the resource indirection pointer
	IndirectionPointer<Resource>* GetResourceIndirectionPointer(unsigned int _resourceIndex);

	// Set a resource allocation method
	void SetResourceAllocationFunctor(unsigned int _resourceIndex, Resource*(*_createResourceFunctor)());

	// Insert a resource into memory
	void SetResourceToMemory(Resource* resource, unsigned int _resourceIndex);

	// Return a resource from memory with a given index
	Resource* GetResourceFromMemory(unsigned int _resourceIndex);

private:

	// The resource locator data
	std::vector<ResourceLocatorData> m_ResourceLocatorData;


};