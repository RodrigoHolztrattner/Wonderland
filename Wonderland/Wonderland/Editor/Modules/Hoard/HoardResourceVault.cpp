////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResourceVault.h"

Hoard::HoardResourceVault::HoardResourceVault()
{
	// Set the initial data
	// ...
}

Hoard::HoardResourceVault::~HoardResourceVault()
{
}

bool Hoard::HoardResourceVault::Initialize()
{

	return true;
}

Hoard::HoardResource* Hoard::HoardResourceVault::IsResourceLoaded(uint32_t _resourceIdentifier)
{
	// For each external resource loaded
	for (auto& resourceHolder : m_Resources)
	{
		// Compare the resource paths
		if (resourceHolder.resourceIdentifier == _resourceIdentifier)
		{
			return resourceHolder.resource;
		}
	}

	return nullptr;
}

void Hoard::HoardResourceVault::InsertResource(HoardResource* _resource, uint32_t _resourceIdentifier)
{
	ResourceHolder resourceHolder = {};
	resourceHolder.resource = _resource;
	resourceHolder.resourceIdentifier = _resourceIdentifier;

	m_Resources.push_back(resourceHolder);
}