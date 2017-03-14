////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceLoader.h"
#include "..\VWContext.h"
#include "VWResource.h"
#include "..\..\GlobalInstance.h"
#include "..\..\Packet\Packet.h"

VulkanWrapper::VWResourceLoader::VWResourceLoader()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWResourceLoader::~VWResourceLoader()
{
}

bool VulkanWrapper::VWResourceLoader::Initialize()
{
	// Start the load process thread
	m_LoadThread = std::thread(&VulkanWrapper::VWResourceLoader::LoadProcess, this);

	return true;
}

void VulkanWrapper::VWResourceLoader::QueueResourceLoad(Reference::Blob<VWResource>* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _processResourceMethod)
{
	ResourceOrder newOrder = {};
	newOrder.resourceReference = _resourceReference;
	newOrder.resourceIdentifier = _resourceIdentifier;
	newOrder.resourceProcessMethod = _processResourceMethod;
	m_TemporaryQueue.push_back(newOrder);
}

void VulkanWrapper::VWResourceLoader::CommitLoadQueues()
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);
	
	// Merge the queue
	m_OrderQueue.insert(m_OrderQueue.end(), m_TemporaryQueue.begin(), m_TemporaryQueue.end());

	// Clear the temporary queue
	m_TemporaryQueue.clear();
}

void VulkanWrapper::VWResourceLoader::LoadProcess()
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

bool VulkanWrapper::VWResourceLoader::TryLoadingResource(ResourceOrder& _resourceOrder)
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

#include <fstream>
#include <iostream>

void VulkanWrapper::VWResourceLoader::LoadResource(ResourceOrder* _resourceOrder)
{
	// Get the order resource ptr
	VWResource* resource = _resourceOrder->resourceReference->GetResource();

	// Set that we are loading this resource
	resource->SetStatus(VWResource::ResourceStatus::Loading);

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
	resource->SetStatus(VWResource::ResourceStatus::Loaded);
}