////////////////////////////////////////////////////////////////////////////////
// Filename: IResource.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IResource_H_
#define _IResource_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <unordered_map>
#include "String\FHashedString.h"

/////////////
// DEFINES //
/////////////

/*
	=> Resource (texture and mesh will extend this class)

		- Only one type of each resource exist at the same time
		- Resource are shared object data
		- They can only be deleted when no other object is referencing them
		- Can use a rule for deletion
*/

// We know the File IO class
class FFileIO;

#include "FResourceCache.h"
#include "FResourceLoader.h"
#include "FResourceManager.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: IResource
////////////////////////////////////////////////////////////////////////////////
class IResource
{
private:

	// Declare the friend classes
	friend FResourceCache;
	friend FResourceManager;
	friend FResourceLoader;

public:

	// Release this resource (remember always to call this when the resource is not needed anymore)
	virtual void Release();

protected:

	// Constructor, copy-constructor and destructor must be private
	IResource();
	IResource(const IResource&);
	~IResource();

	// Load this resource (protected because this will be called by the GetResource() method (and not by the user))
	virtual void Load(unsigned char* _resourceData) = 0;

	// Update this resource
	virtual void Update(float _time) = 0;

private:

	// Return the reference count
	unsigned int GetReferenceCount()
	{
		return m_ReferenceCount;
	}

	// Increment the reference count
	void IncrementReferences()
	{
		m_ReferenceCount++;
	}

	// Decrement the reference count
	void DecrementReferences()
	{
		m_ReferenceCount--;
	}

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Initialize the resource system
	static bool InitializeResourceSystem(const char* _mainDataHeaderName);

	// <GLOBAL> Return a resource using a hashed string
	template <typename ResourceType>
	static ResourceType* GetResourceByName(FHashedString _resourceHash)
	{
		IResource* resource;
		FResourceManager::ResourceHeader* resourceHeader;

		// Check if the resource is already loaded
		resource = m_ResourceCache->GetLoadedResource(_resourceHash);
		if (resource != nullptr)
		{
			// USE A SAFE CAST HERE!
			return (ResourceType*)resource;
		}

		// Create the resource
		resource = new ResourceType;

		// Increase references , this sets the references count to 1
		resource->IncrementReferences();

		// Insert the created resource into the cache
		m_ResourceCache->InsertLoadedResource(_resourceHash, resource);

		// Call the log class
		LResourceLog::PrintResourceCreated(resource);

		// Check if the resource exist inside our database
		resourceHeader = m_ResourceManager->GetResourceHeader(_resourceHash);
		if (resourceHeader != nullptr)
		{
			// Load the resource
			if (!m_ResourceLoader->LoadResource(resourceHeader, resource))
			{
				return nullptr;
			}

			// USE A SAFE CAST HERE!
			return (ResourceType*)resource;
		}

		// Check if we can load the resource from the local folder
		if (!m_ResourceLoader->LoadResourceFromLocalFolder(_resourceHash.String(), resource))
		{
			return nullptr;
		}

		// USE A SAFE CAST HERE!
		return (ResourceType*)resource;
	}

	// <GLOBAL> Update the resource system
	static void UpdateResourceSystem(float _time);

private:

	// The reference count
	unsigned int m_ReferenceCount;

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The resource cache, manager and loader objects
	static FResourceCache* m_ResourceCache;
	static FResourceManager* m_ResourceManager;
	static FResourceLoader* m_ResourceLoader;
};

#include <iostream>
////////////////////////////////////////////////////////////////////////////////
// Class name: IResourceLog
////////////////////////////////////////////////////////////////////////////////
class LResourceLog
{
	enum LogForce
	{
		Null,
		Watch,
		Weak,
		Normal,
		Strong
	};

	// Resource is a friend class
	friend IResource;

	// This will tell the pre-processor the log force
	static const int LogForce = Null;

	// The resource that we are listening
	static IResource* ResourceWatch;

public:

	// Set the watch
	void SetWatch(IResource* _who)
	{
		ResourceWatch = _who;
	}

	// Print the number of resources
	inline static void PrintNumberResources()
	{
		// if (LogForce >= LogForce::Weak)
			// std::cout << "=> Number of resources: " << (IResource::GetResourcesReference())->size() << std::endl;
	}

	// Tell that a resource was created
	inline static void PrintResourceCreated(IResource* _who)
	{
		if (LogForce == LogForce::Watch)
		{
			if (ResourceWatch == _who)
				std::cout << "=> Resource with ID: " << (unsigned int)_who << " was created." << std::endl;
		}
		else if (LogForce >= LogForce::Strong)
			std::cout << "=> Resource with ID: " << (unsigned int)_who << " was created." << std::endl;
	}

	// Tell that a resource was deleted
	inline static void PrintResourceDeleted(IResource* _who)
	{
		if (LogForce == LogForce::Watch)
		{
			if (ResourceWatch == _who)
				std::cout << "=> Resource with ID: " << (unsigned int)_who << " was deleted." << std::endl;
		}
		else if (LogForce >= LogForce::Strong)
			std::cout << "=> Resource with ID: " << (unsigned int)_who << " was deleted." << std::endl;
	}

	// Tell that a resource was referenced
	inline static void PrintResourceReferenced(IResource* _who)
	{
		if (LogForce == LogForce::Watch)
		{
			if (ResourceWatch == _who)
				std::cout << "=> Resource with ID: " << (unsigned int)_who << " was referenced." << std::endl;
		}
		else if (LogForce >= LogForce::Strong)
			std::cout << "=> Resource with ID: " << (unsigned int)_who << " was referenced." << std::endl;
	}

	// Tell that a resource was released
	inline static void PrintResourceReleased(IResource* _who)
	{
		if (LogForce == LogForce::Watch)
		{
			if (ResourceWatch == _who)
				std::cout << "=> Resource with ID: " << (unsigned int)_who << " was released." << std::endl;
		}
		else if (LogForce >= LogForce::Strong)
			std::cout << "=> Resource with ID: " << (unsigned int)_who << " was released." << std::endl;
	}
};



#endif
