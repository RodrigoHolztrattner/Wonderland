////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardSupplyManager.h"
#include "HoardSupplyObject.h"
#include "..\..\LogSystem.h"
#include "..\..\Peon\Peon.h"

/*
Hoard::Supply::HoardSupplyManager::HoardSupplyManager()
{
	// Set the initial data
	// ...
}

Hoard::Supply::HoardSupplyManager::~HoardSupplyManager()
{
}

bool Hoard::Supply::HoardSupplyManager::Initialize(HoardSupplyIndexLoader* _indexLoaderRef, uint32_t _totalWorkerThreads)
{
	// Set the texture group index loader reference
	m_IndexLoader = _indexLoaderRef;

	// Set the total worker threads
	m_TotalWorkerThreads = _totalWorkerThreads;

	// Alloc the resource requests
	m_Requests = new std::vector<HoardSupplyRequest>[_totalWorkerThreads];

	// Initialize the texture group vault
	if (!m_Vault.Initialize())
	{
		return false;
	}

	return true;
}

void Hoard::Supply::HoardSupplyManager::Release()
{

}

void Hoard::Supply::HoardSupplyManager::RequestObject(Reference::Blob<HoardSupplyObject>* _objecteference, HashedStringIdentifier _identifier)
{
	// Get the current worker index
	uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

	// Create a new resource request
	HoardSupplyRequest newRequest = {};
	newRequest.Create(_objecteference, _identifier);

	// Insert into the queue
	m_Requests[currentWorkerIndex].push_back(newRequest);
}

void Hoard::Supply::HoardSupplyManager::ProcessRequestQueues(HoardResourceManager* _resourceManager)
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

void Hoard::Supply::HoardSupplyManager::ProcessRequest(HoardResourceManager* _resourceManager, HoardSupplyRequest& _request)
{
	// Check if the texture group is inside the vault
	HoardSupplyObject* object = m_Vault.IsLoaded(_request.GetRequestIdentifier());
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
	HoardSupplyObject* newObject = CreateAndRequestObject(_resourceManager, newObjectIndex->GetResourceIdentifier());
	
	// Insert the texture group into the vault
	m_Vault.Insert(newObject, _request.GetRequestIdentifier());

	// Set the resource ptr
	_request.GetRequestReference()->ValidateResourceReference(newObject);
}

Hoard::Supply::HoardSupplyObject* Hoard::Supply::HoardSupplyManager::CreateAndRequestObject(HoardResourceManager* _resourceManager, uint32_t _resourceIdentifier)
{
	// Create a new object
	HoardSupplyObject* newObject = CreateNewObject();

	// Initialize the new object
	newObject->Initialize();

	// Request the new resource
	_resourceManager->RequestResource(newObject->GetResourceReference(), _resourceIdentifier, []() {}, [=]() {});

	return newObject;
}
*/