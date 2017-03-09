///////////////////////////////////////////////////////////////////////////////
// Filename: FResourceCache.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FResourceCache.h"
#include "IResource.h"

FResourceCache::FResourceCache()
{
}

FResourceCache::FResourceCache(const FResourceCache& other)
{
}

FResourceCache::~FResourceCache()
{
}

bool FResourceCache::Initialize()
{
	return true;
}

////////////
// GLOBAL //
////////////

IResource* FResourceCache::GetLoadedResource(FHashedString _resourceName)
{
	// Try to find the resource
	std::unordered_map<FHashedString, IResource*, FHashedString::Hasher, FHashedString::Equal>::iterator resource = m_MappedResources.find(_resourceName);

	// Check if we found it
	if (resource != m_MappedResources.end())
	{
		// Increment the references
		(*resource).second->IncrementReferences();

		// Call the log class
		LResourceLog::PrintResourceReferenced((*resource).second);

		// Return the resource (USE A CUSTOM CAST HERE)
		return (*resource).second;
	}

	// If we are here, the resource doesnt exist inside our database //
	return nullptr;
}

void FResourceCache::InsertLoadedResource(FHashedString _resourceName, IResource* _resource)
{
	// Insert into the map
	m_MappedResources.insert(std::pair<FHashedString, IResource*>(_resourceName, _resource));
}

void FResourceCache::UpdateResources(float _time)
{
	// Start the iteration
	std::unordered_map<FHashedString, IResource*, FHashedString::Hasher, FHashedString::Equal>::iterator iterator = m_MappedResources.begin();

	while (iterator != m_MappedResources.end())
	{
		// Check if this resource should be updated or deleted
		if ((*iterator).second->GetReferenceCount())
		{
			// Update this resource
			(*iterator).second->Update(_time);

			// Go to the next resource
			iterator++;
		}
		else
		{
			// Call the log class
			LResourceLog::PrintResourceDeleted((*iterator).second);

			// Delete the resource
			delete (*iterator).second;

			// Remove from the map
			iterator = m_MappedResources.erase(iterator);
		}
	}
}