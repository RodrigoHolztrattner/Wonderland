////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HoardResourceLoader.h"
#include "HoardResource.h"
#include "..\GlobalInstance.h"
#include "..\Packet\Packet.h"
#include <fstream>
#include <iostream>

Hoard::HoardResourceLoader::HoardResourceLoader()
{
	// Set the initial data
	// ...
}

Hoard::HoardResourceLoader::~HoardResourceLoader()
{
}

bool Hoard::HoardResourceLoader::Initialize()
{
	// Start the load process thread
	m_LoadThread = std::thread(&Hoard::HoardResourceLoader::LoadProcess, this);

	return true;
}

void Hoard::HoardResourceLoader::QueueResourceLoad(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _processResourceMethod)
{
	ResourceOrder newOrder = {};
	newOrder.resourceReference = _resourceReference;
	newOrder.resourceIdentifier = _resourceIdentifier;
	newOrder.resourceProcessMethod = _processResourceMethod;
	m_TemporaryQueue.push_back(newOrder);
}

void Hoard::HoardResourceLoader::CommitLoadQueues()
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);
	
	// Merge the queue
	m_OrderQueue.insert(m_OrderQueue.end(), m_TemporaryQueue.begin(), m_TemporaryQueue.end());

	// Clear the temporary queue
	m_TemporaryQueue.clear();
}

void Hoard::HoardResourceLoader::LoadProcess()
{
	// Until our application finish
	while (true)
	{
		// Try to get a new  load order
		ResourceOrder loadOrder = {};
		if (TryLoadingResource(loadOrder))
		{
			// Load this internal resource
			LoadResource(&loadOrder);

			continue;
		}


		// No orders to load, just yield our time slice
		std::this_thread::yield();
	}
}

bool Hoard::HoardResourceLoader::TryLoadingResource(ResourceOrder& _resourceOrder)
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);

	// Check the size
	if (m_OrderQueue.size())
	{
		// Get the load order and remove it from the queue
		_resourceOrder = m_OrderQueue[0];
		m_OrderQueue.erase(m_OrderQueue.begin() + 0); //TODO: usar o ultimo objeto para facilitar
		
		return true;
	}

	return false;
}

void Hoard::HoardResourceLoader::LoadResource(ResourceOrder* _resourceOrder)
{
	// Get the order resource ptr
	HoardResource* resource = _resourceOrder->resourceReference->GetResource();

	// Set that we are loading this resource
	resource->SetStatus(HoardResource::ResourceStatus::Loading);

	// Get the packet manager global instance
	GlobalInstance<Packet::Manager> PacketManager;

	// Get the resource byte array data
	std::vector<unsigned char>& resourceByteArrayData = resource->GetByteArrayData();

	// Get the file from the packet manager
	Packet::File* resourceFile = PacketManager->FindFile(_resourceOrder->resourceIdentifier);
	if (resourceFile == nullptr)
	{
		// The file doesnt exist!
		return;
	}

	// Load the file
	if (!PacketManager->LoadFile(resourceFile, resourceByteArrayData))
	{
		// Error loading the resource file
		return;
	}

	// Call the process resource method
	_resourceOrder->resourceProcessMethod();

	// Set the loaded status
	resource->SetStatus(HoardResource::ResourceStatus::Loaded);
}