///////////////////////////////////////////////////////////////////////////////
// Filename: IResource.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IResource.h"

IResource::IResource()
{
	// Set the initial reference count to 0
	m_ReferenceCount = 0;
}

IResource::IResource(const IResource& other)
{
}

IResource::~IResource()
{
}

void IResource::Release()
{
	// Call the log class
	LResourceLog::PrintResourceReleased(this);

	// Decrement the reference count
	DecrementReferences();
}

// The resource log "watch" initialization
IResource* LResourceLog::ResourceWatch = nullptr;

////////////
// GLOBAL //
////////////
#include "FResourceCache.h"
#include "FResourceManager.h"
#include "FResourceLoader.h"

// Set a null ptr for the resource cache, the resource manager and the resource loader
FResourceCache* IResource::m_ResourceCache = nullptr;
FResourceManager* IResource::m_ResourceManager = nullptr;
FResourceLoader* IResource::m_ResourceLoader = nullptr;

bool IResource::InitializeResourceSystem(const char* _mainDataHeaderName)
{
	// Create the resource manager
	m_ResourceManager = new FResourceManager;
	if (m_ResourceManager == nullptr)
	{
		return false;
	}

	// Create the resource cache
	m_ResourceCache = new FResourceCache;
	if (m_ResourceCache == nullptr)
	{
		return false;
	}

	// Create the resource loader
	m_ResourceLoader = new FResourceLoader;
	if (m_ResourceLoader == nullptr)
	{
		return false;
	}

	// Initialize the resource manager
	if (!m_ResourceManager->Initialize(_mainDataHeaderName))
	{
		return false;
	}

	// Initialize the resource cache
	if (!m_ResourceCache->Initialize())
	{
		return false;
	}

	// Initialize the resource loader
	if (!m_ResourceLoader->Initialize())
	{
		return false;
	}

	return true;
}

void IResource::UpdateResourceSystem(float _time)
{
	// Update the resource cache
	m_ResourceCache->UpdateResources(_time);

	// Update the resource loader
	m_ResourceLoader->UpdateResourceQueue(_time);
}