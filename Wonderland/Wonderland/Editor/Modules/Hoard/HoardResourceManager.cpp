////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResourceManager.h"
#include "..\Peon\Peon.h"
#include "..\Packet\Packet.h"
#include "..\GlobalInstance.h"

Hoard::HoardResourceManager::HoardResourceManager()
{
	// Set the initial data
	m_TotalWorkerThreads = 0;
	m_ResourceWakeList = nullptr;
}

Hoard::HoardResourceManager::~HoardResourceManager()
{
}

bool Hoard::HoardResourceManager::Initialize(uint32_t _totalWorkerThreads)
{
	// Set the total worker threads
	m_TotalWorkerThreads = _totalWorkerThreads;

	// Alloc the resource requests
	m_ResourceRequests = new std::vector<HoardResourceRequest>[_totalWorkerThreads];

	// Initialize the resource loader
	if(!m_ResourceLoader.Initialize())
	{
		return false;
	}

	return true;
}

void Hoard::HoardResourceManager::RequestResource(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _onLoadCallback, std::function<void()> _processMethod)
{
	// Get the current worker index
	uint32_t currentWorkerIndex = Peon::GetCurrentWorkerIndex();

	// Create a new resource request
	HoardResourceRequest newRequest = {};
	newRequest.Create(_resourceReference, _resourceIdentifier, _onLoadCallback, _processMethod);

	// Insert into the queue
	m_ResourceRequests[currentWorkerIndex].push_back(newRequest);
}

void Hoard::HoardResourceManager::RequestResource(Reference::Blob<HoardResource>* _resourceReference, std::string _resourcePath, std::function<void()> _onLoadCallback, std::function<void()> _processMethod)
{	
	// Get the packet manager global instance
	GlobalInstance<Packet::Manager> PacketManager;

	// Find the file using the resource path
	Packet::File* resourceFile = PacketManager->FindFile(_resourcePath.c_str(), false);
	if (resourceFile == nullptr) 
	{
		// Error, we cant find the file!
		return;
	}

	// Request the resource using the file internal identifier
	return RequestResource(_resourceReference, resourceFile->GetIdentifier(), _onLoadCallback, _processMethod);
}

void Hoard::HoardResourceManager::ProcessResourceRequestQueues()
{
	// Process our wake list first
	ProcessWakeList();

	// Process and clear all request queues
	for (int i = 0; i < m_TotalWorkerThreads; i++)
	{
		// Process all requests for this queue
		for (auto& resourceRequest : m_ResourceRequests[i])
		{
			// Process this request
			ProcessResourceRequest(resourceRequest);
		}

		// Clear this request queue
		m_ResourceRequests[i].clear();
	}

	// Commit all resource requests for loading
	m_ResourceLoader.CommitLoadQueues();
}

void Hoard::HoardResourceManager::ProcessWakeList()
{
	// Set the dummy pointer
	HoardResource dummyPointer = {};
	dummyPointer.next = m_ResourceWakeList;

	// For each resource inside our list
	HoardResourceBase* currentResource = m_ResourceWakeList;
	HoardResource* lastResource = &dummyPointer;
	while (currentResource != nullptr)
	{
		// Check if this resource is loaded
		if (currentResource->GetStatus() == HoardResource::ResourceStatus::Loaded)
		{
			// Process all wake callbacks
			currentResource->ProcessWakeCallbacks();

			// Set the initialized status
			currentResource->SetStatus(HoardResource::ResourceStatus::Initialized);

			// Make the last resource point to the next one from this
			lastResource->next = currentResource->next;
			currentResource = currentResource->next;
		}
	}

	// Set the list start
	m_ResourceWakeList = dummyPointer.next;
}

void Hoard::HoardResourceManager::ProcessInternalResourceRequest(HoardResourceRequest& _resourceRequest)
{
	return;
}

void Hoard::HoardResourceManager::ProcessResourceRequest(HoardResourceRequest& _resourceRequest)
{
	// Check if the resource is inside the vault
	HoardResource* resource = m_ResourceVault.IsResourceLoaded(_resourceRequest.GetRequestIdentifier());
	if (resource != nullptr)
	{
		// Check if the resource was initialized
		if (resource->GetStatus() == HoardResource::ResourceStatus::Initialized)
		{
			// Call the wake callback
			_resourceRequest.GetWakeCallback()();
		}
		else
		{
			// Append another wake callback
			resource->InsertWakeCallback(_resourceRequest.GetWakeCallback());
		}

		// Increment the resource reference counter
		resource->IncrementReferenceCount();

		// Set the resource ptr
		_resourceRequest.GetResourceReference()->ValidateResourceReference(resource);

		return;
	}

	// Create a new resource object
	HoardResource* newResource = new HoardResource();

	// Append this new resource to the wake list
	newResource->next = m_ResourceWakeList;
	m_ResourceWakeList = newResource;

	// Initialize the new resource
	newResource->Initialize();

	// Append the resource callback
	newResource->InsertWakeCallback(_resourceRequest.GetWakeCallback());

	// Queue the resource load
	m_ResourceLoader.QueueResourceLoad(_resourceRequest.GetResourceReference(), _resourceRequest.GetRequestIdentifier(), _resourceRequest.GetProcessMethod());

	// Insert the resource into the vault
	m_ResourceVault.InsertResource(newResource, _resourceRequest.GetRequestIdentifier());

	// Set the resource ptr
	_resourceRequest.GetResourceReference()->ValidateResourceReference(newResource);
}