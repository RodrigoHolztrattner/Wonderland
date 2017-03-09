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

VulkanWrapper::VWResource* VulkanWrapper::VWResourceVault::IsInternalResourceLoaded(uint32_t _resourceIdentifier)
{
	return nullptr;
}

VulkanWrapper::VWResource* VulkanWrapper::VWResourceVault::IsExternalResourceLoaded(std::string _resourcePath)
{
	// For each external resource loaded
	for (auto& resourceHolder : m_ExternalResources)
	{
		// Compare the resource paths
		if(!resourceHolder.resourcePath.compare(_resourcePath))
		{
			return resourceHolder.resource;
		}
	}

	return nullptr;
}

void VulkanWrapper::VWResourceVault::InsertExternalResource(VWResource* _resource, std::string _resourcePath)
{
	ExternalResourceHolder resourceHolder = {};
	resourceHolder.resource = _resource;
	resourceHolder.resourcePath = _resourcePath;

	m_ExternalResources.push_back(resourceHolder);
}