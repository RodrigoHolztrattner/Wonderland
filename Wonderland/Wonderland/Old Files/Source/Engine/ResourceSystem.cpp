////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceSystem.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ResourceSystem.h"
#include <atomic>

///////////////
// NAMESPACE //
///////////////

ResourceSystem::ResourceSystem()
{
}

ResourceSystem::ResourceSystem(const ResourceSystem& other)
{
}

ResourceSystem::~ResourceSystem()
{
}

bool ResourceSystem::Initialize(EngineConfig _engineConfig)
{
	// Initialize the resource metadata
	if (!m_ResourceMetadata.Initialize())
	{
		return false;
	}

	// Initialize the resource locator
	if (!m_ResourceLocator.Initialize(m_ResourceMetadata.GetNumberResources()))
	{
		return false;
	}

	// Initialize the resource cache
	if (!m_ResourceCache.Initialize(1024, 2))
	{
		return false;
	}

	//
	//
	//

	// Get the number of resource workers
	unsigned int numberResourceWorkers = 2;

	// Create the resource workers
	m_ResourceWorkers = new ResourceWorkerThread[numberResourceWorkers];

	// Foe each resource worker
	for (int i = 0; i < numberResourceWorkers; i++)
	{
		// Initialize this resource worker
		if (!m_ResourceWorkers[i].Initialize())
		{
			return false;
		}
	}

	return true;
}

/*
IndirectionPointer<Resource>* ResourceSystem::GetResource(FHashId _hashId)
{
	// Get the resource index
	unsigned int resourceIndex = m_ResourceMetadata.GetResourceIndex(_hashId);
	if (resourceIndex == -1)
	{
		return nullptr;
	}

	// Make a request to this resource
	// ...

	// Return the indirection pointer for this resource
	return m_ResourceLocator.GetResourceIndirectionPointer(resourceIndex);



	//
	//
	//



	/*
		- Qualquer thread pode tentar solicitar um recurso, a entrada deles até aqui não é um problema.
		- Existem 2 opções quando se solicita o recurso, OU ele é enviado na hora OU ele é encaminhado para ser enviado.
		- A função abaixo determina se ele já está carregado. Caso uma thread consiga acesso à esta função, pode-se entender que o recurso EXISTE a partir daí
		e que ele é válido (afinal se uma thread conseguiu solicitar o recurso, ele OU existe OU será criado, então logo o ponteiro do mesmo é válido).
	
	*/
	
	/*

	// Check if the resource is loaded
	Resource* resource = m_ResourceLocator.GetResourceFromMemory(resourceIndex);
	if (resource != nullptr)
	{
		// We found the resource! Increment the number of references
		resource->IncrementReferences(); // Atomic

		return resource;
	}

	//
	//	Daqui para baixo é trabalho das worker threads
	//

	// Check if the resource exist inside the cache
	resource = m_ResourceCache.FindResource(_hashId);
	if (resource != nullptr)
	{
		// We found the resource inside the cache! //

		// Insert the resource into the locator data
		m_ResourceLocator.SetResourceToMemory(resource, resourceIndex);

		// Increment the references
		resource->IncrementReferences(); // Atomic

		return resource;
	}

	return nullptr;
}
*/

void ResourceSystem::Shutdown()
{

}