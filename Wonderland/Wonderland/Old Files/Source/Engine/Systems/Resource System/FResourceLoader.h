////////////////////////////////////////////////////////////////////////////////
// Filename: FResourceLoader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FResourceLoader_H_
#define _FResourceLoader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <unordered_map>
#include "Containers\Array\TArray.h"
#include "Thread\FThread.h"
#include "File\FFileIO.h"
#include "String\FHashedString.h"

/////////////
// DEFINES //
/////////////

/*
	=> We use the pre-created singleton pattern to this class
	(the object will be created when the engine initializes itself and a ptr will be stored to reference this object)

	=> This class manage the loading of resource objects (using threads)
*/

// We know the IResource class
class IResource;

#include "FResourceManager.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: FResourceLoader
////////////////////////////////////////////////////////////////////////////////
class FResourceLoader
{
private:
	
	// The resource queue type
	struct ResourceQueue
	{
		ResourceQueue(IResource* _resource, FResourceManager::ResourceHeader* _resourceHeader) : resource(_resource), resourceHeader(_resourceHeader){}
		ResourceQueue(){}
		ResourceQueue(const ResourceQueue& other)
		{
			resource = other.resource;
			resourceHeader = other.resourceHeader;
		}

		// The resource object
		IResource* resource;

		// The resource header
		FResourceManager::ResourceHeader* resourceHeader;
	};

	// The resource data type
	struct ResourceData
	{
		// The worker thread object that will load any data here
		FThread<FResourceManager::ResourceHeader> workerThread;

		// The data IO that will manage this resource data
		FFileIO dataIO;

		// The current resource that we are loading here
		IResource* currentResource;

		// The queued objects that need to be loaded
		TArray<ResourceQueue> queuedObjects;
	};

public:

	FResourceLoader();
	FResourceLoader(const FResourceLoader&);
	~FResourceLoader();

	// Initialize the resource loader
	bool Initialize();

public:

	// Load a resource or queue the load
	template <typename ResourceClass>
	bool LoadResource(FResourceManager::ResourceHeader* _resourceHeader, ResourceClass* _resourceObject)
	{
		// Get the worker thread object
		FThread<FResourceManager::ResourceHeader> workerThread = m_ResourceData[_resourceHeader->dataIndex].workerThread;

		// Check if the worker thread is free
		if (workerThread.Free())
		{
			// THREADED //

			// Set the current resource
			m_ResourceData[_resourceHeader->dataIndex].currentResource = _resourceObject;

			// Dispatch the thread to load the resource
			workerThread.Dispatch(WCallback<FResourceManager::ResourceHeader>(*this, &FResourceLoader::LoadHelper), _resourceHeader);
		}
		else
		{
			// Add the resource to the queue
			m_ResourceData[_resourceHeader->dataIndex].queuedObjects.Add(ResourceQueue(_resourceObject, _resourceHeader));
		}

		// => Precisa criar uma função intermediária que faz a decompressão do arquivo(pode ser uma função de ajuda da LOAD dentro do IResource).
		// => Tem que ver se não vão existir problemas gerais já que estamos utilizando um tipo de criação do ResourceHeader para arquivos locais...
		// mas acho que se realizarmos o que foi dito na primeira observação e verificar se o arquivo é local, tudo estará ok.

		// Return true because we found the resource
		return true;
	}

	// Load a resource from the local folder
	template <typename ResourceClass>
	bool LoadResourceFromLocalFolder(const char* _resourcePath, ResourceClass* _resourceObject)
	{
		// NOT THREADED //

		// Set the current local resource
		m_CurrentLocalResource = _resourceObject;

		// Create a temporary resource header
		FResourceManager::ResourceHeader resourceHeader(_resourcePath);

		// Call the load helper function
		LoadHelper(&resourceHeader);

		return true;
	}

	// Update the resource queue
	void UpdateResourceQueue(float _time);

private:

	// The helper class for loading resources
	void LoadHelper(FResourceManager::ResourceHeader* _resourceHeader);

private:

	// The resource data
	ResourceData* m_ResourceData;

	// The resource that we are current loading (only for local files)
	IResource* m_CurrentLocalResource;
};

#endif
