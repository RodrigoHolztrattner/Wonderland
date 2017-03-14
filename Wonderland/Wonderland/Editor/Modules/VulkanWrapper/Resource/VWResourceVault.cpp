////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceVault.h"
#include "..\VWContext.h"

VulkanWrapper::VWResourceVault::VWResourceVault()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWResourceVault::~VWResourceVault()
{
}

bool VulkanWrapper::VWResourceVault::Initialize()
{

	return true;
}

VulkanWrapper::VWResource* VulkanWrapper::VWResourceVault::IsResourceLoaded(uint32_t _resourceIdentifier)
{
	// For each external resource loaded
	for (auto& resourceHolder : m_Resources)
	{
		// Compare the resource paths
		if (!resourceHolder.resourceIdentifier == _resourceIdentifier)
		{
			return resourceHolder.resource;
		}
	}

	return nullptr;
}

void VulkanWrapper::VWResourceVault::InsertResource(VWResource* _resource, uint32_t _resourceIdentifier)
{
	ResourceHolder resourceHolder = {};
	resourceHolder.resource = _resource;
	resourceHolder.resourceIdentifier = _resourceIdentifier;

	m_Resources.push_back(resourceHolder);
}