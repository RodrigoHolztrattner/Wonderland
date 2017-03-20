////////////////////////////////////////////////////////////////////////////////
// Filename: HoardSupplyManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"
#include "..\..\Reference.h"
#include "..\..\Peon\Peon.h"

#include "..\HoardResourceManager.h"

#include "HoardSupplyIndexLoader.h"
#include "HoardSupplyObject.h"
#include "HoardSupplyRequest.h"
#include "HoardSupplyVault.h"
#include "HoardSupplyIndex.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <functional>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Hoard Resource Module
NamespaceBegin(Hoard)

// Hoard Resource Supply Module
NamespaceBegin(Supply)

////////////////
// FORWARDING //
////////////////

class HoardSupplyObject;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardSupplyManager
////////////////////////////////////////////////////////////////////////////////
//typedef HoardSupplyObject ObjectType;
template <typename ObjectType, typename IndexType>
class HoardSupplyManager
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardSupplyManager() {}
	~HoardSupplyManager() {}

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(HoardSupplyIndexLoader<IndexType>* _indexLoaderRef, uint32_t _totalWorkerThreads)
	{
		// Set the texture group index loader reference
		m_IndexLoader = _indexLoaderRef;

		// Set the total worker threads
		m_TotalWorkerThreads = _totalWorkerThreads;

		// Alloc the resource requests
		m_Requests = new std::vector<HoardSupplyRequest<ObjectType>>[_totalWorkerThreads];

		// Initialize the texture group vault
		if (!m_Vault.Initialize())
		{
			return false;
		}

		return true;
	}

	// Release this image
	virtual void Release()
	{

	}

	// Request an object
	void RequestObject(Reference::Blob<ObjectType>* _objectReference, HashedStringIdentifier _groupIdentifier)
	{
		// Get the current worker index
		uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

		// Create a new resource request
		HoardSupplyRequest<ObjectType> newRequest = {};
		newRequest.Create(_objectReference, _groupIdentifier);

		// Insert into the queue
		m_Requests[currentWorkerIndex].push_back(newRequest);
	}

	// Request an object
	void RequestObject(Reference::Blob<ObjectType>* _objectReference, const char* _objectNameIdentifier)//TODO: usar apenas a função acima ou verificar que essa aqui faz o hash em tempo de compilação
	{
		// Get the current worker index
		uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

		// Create a new resource request
		HoardSupplyRequest<ObjectType> newRequest = {};
		newRequest.Create(_objectReference, HashedString(_objectNameIdentifier).Hash());

		// Insert into the queue
		m_Requests[currentWorkerIndex].push_back(newRequest);
	}

	// Process object requests
	void ProcessRequestQueues(HoardResourceManager* _resourceManager)
	{
		// Process and clear all request queues
		for (int i = 0; i < m_TotalWorkerThreads; i++)
		{
			// Process all requests for this queue
			for (auto& resourceRequest : m_Requests[i])
			{
				// Process this request
				ProcessRequest(_resourceManager, resourceRequest);
			}

			// Clear this request queue
			m_Requests[i].clear();
		}
	}

protected:

	// Create a new supply object and request the resource loading
	virtual ObjectType* CreateAndRequestObject(HoardResourceManager* _resourceManager, uint32_t _resourceIdentifier)
	{
		// Create a new object
		ObjectType* newObject = new ObjectType();

		// Initialize the new object
		newObject->Initialize();

		// Request the new resource
		_resourceManager->RequestResource(newObject->GetResourceReference(), _resourceIdentifier, []() {}, [=]() {});

		return newObject;
	}

private:

	// Process an object request
	void ProcessRequest(HoardResourceManager* _resourceManager, HoardSupplyRequest<ObjectType>& _request)
	{
		// Check if the texture group is inside the vault
		ObjectType* object = m_Vault.IsLoaded(_request.GetRequestIdentifier());
		if (object != nullptr)
		{
			// Set the resource ptr
			_request.GetRequestReference()->ValidateResourceReference(object);

			return;
		}

		// Get the object index for the current request
		HoardSupplyIndex* newObjectIndex = m_IndexLoader->GetIndex(_request.GetRequestIdentifier());
		if (newObjectIndex == nullptr)
		{
			// Error, the request object identifier dont exist inside the index loader!
			return;
		}

		// Create and request a new object
		ObjectType* newObject = CreateAndRequestObject(_resourceManager, newObjectIndex->GetResourceIdentifier());
		if (newObject == nullptr)
		{
			// Unknow error!
			return;
		}

		// Insert the texture group into the vault
		m_Vault.Insert(newObject, _request.GetRequestIdentifier());

		// Set the resource ptr
		_request.GetRequestReference()->ValidateResourceReference(newObject);
	}

///////////////
// VARIABLES //
private: //////

	// The total number of worker threads we are using
	uint32_t m_TotalWorkerThreads;

	// Our requests
	std::vector<HoardSupplyRequest<ObjectType>>* m_Requests;

	// Our vault
	HoardSupplyVault<ObjectType> m_Vault;

	// The index loader reference
	HoardSupplyIndexLoader<IndexType>* m_IndexLoader;
};

// Hoard Resource Supply Module
NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)