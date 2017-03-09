////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceLocator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ResourceLocator.h"

///////////////
// NAMESPACE //
///////////////

ResourceLocator::ResourceLocator()
{
}

ResourceLocator::ResourceLocator(const ResourceLocator& other)
{
}

ResourceLocator::~ResourceLocator()
{
}

bool ResourceLocator::Initialize(unsigned int _numberResources)
{
	// Allocate space for each resource data
	m_ResourceLocatorData.resize(_numberResources);

	// For each resource allocated
	for (int i = 0; i < _numberResources; i++)
	{
		// Set nullptr
		m_ResourceLocatorData[i].resource = new IndirectionPointer<Resource>();
		m_ResourceLocatorData[i].resource->Set(nullptr);
	}

	return true;
}

void ResourceLocator::SetResourceToMemory(Resource* resource, unsigned int _resourceIndex)
{
	// Set the resource object
	m_ResourceLocatorData[_resourceIndex].resource->Set(resource);
}

void ResourceLocator::SetResourceAllocationFunctor(unsigned int _resourceIndex, Resource*(*_createResourceFunctor)())
{
	// Set the resource allocation method
	m_ResourceLocatorData[_resourceIndex].createResourceFunctor = _createResourceFunctor;
}

IndirectionPointer<Resource>* ResourceLocator::GetResourceIndirectionPointer(unsigned int _resourceIndex)
{
	// Check if the index is valid
	if (_resourceIndex < m_ResourceLocatorData.size())
	{
		return m_ResourceLocatorData[_resourceIndex].resource;
	}

	return nullptr;
}

Resource* ResourceLocator::GetResourceFromMemory(unsigned int _resourceIndex)
{
	// Check if the resource is loaded
	if (m_ResourceLocatorData[_resourceIndex].resource->Get() != nullptr)
	{
		return m_ResourceLocatorData[_resourceIndex].resource->Get();
	}

	return nullptr;
}