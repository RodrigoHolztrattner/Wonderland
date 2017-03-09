////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWResourceLoader.h"
#include "..\VWContext.h"
#include "VWResource.h"

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

void VulkanWrapper::VWResourceLoader::QueueInternalResourceLoad(VWResourceReference* _resourceReference, uint32_t _resourceIdentifier)
{
	InternalResourceOrder newOrder = {};
	newOrder.resourceReference = _resourceReference;
	newOrder.resourceIdentifier = _resourceIdentifier;
	m_TemporaryInternalQueue.push_back(newOrder);
}

void VulkanWrapper::VWResourceLoader::QueueExternalResourceLoad(VWResourceReference* _resourceReference, std::string _resourcePath)
{
	ExternalResourceOrder newOrder = {};
	newOrder.resourceReference = _resourceReference;
	newOrder.resourcePath = _resourcePath;
	m_TemporaryExternalQueue.push_back(newOrder);
}

void VulkanWrapper::VWResourceLoader::CommitLoadQueues()
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);
	
	// Merge the queues
	m_InternalOrderQueue.insert(m_InternalOrderQueue.end(), m_TemporaryInternalQueue.begin(), m_TemporaryInternalQueue.end());
	m_ExternalOrderQueue.insert(m_ExternalOrderQueue.end(), m_TemporaryExternalQueue.begin(), m_TemporaryExternalQueue.end());

	// Clear the temporary queues
	m_TemporaryInternalQueue.clear();
	m_TemporaryExternalQueue.clear();
}

void VulkanWrapper::VWResourceLoader::LoadProcess()
{
	// Until our application finish
	while (true)
	{
		// Try to get a new internal load order
		InternalResourceOrder internalLoadOrder = {};
		if (TryLoadingInternalResource(internalLoadOrder))
		{
			// Load this internal resource
			LoadInternalResource(&internalLoadOrder);

			continue;
		}

		// Try to get a new external load order
		ExternalResourceOrder externalLoadOrder = {};
		if (TryLoadingExternalResource(externalLoadOrder))
		{
			// Load this external resource
			LoadExternalResource(&externalLoadOrder);

			continue;
		}

		// No orders to load, just yield our time slice
		std::this_thread::yield();
	}
}

bool VulkanWrapper::VWResourceLoader::TryLoadingInternalResource(InternalResourceOrder& _resourceOrder)
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);

	// Check the size
	if (m_InternalOrderQueue.size())
	{
		// Get the load order and remove it from the queue
		_resourceOrder = m_InternalOrderQueue[0];
		m_InternalOrderQueue.erase(m_InternalOrderQueue.begin() + 0);
		
		return true;
	}

	return false;
}

bool VulkanWrapper::VWResourceLoader::TryLoadingExternalResource(ExternalResourceOrder& _resourceOrder)
{
	// Lock the loading mutex
	std::lock_guard<std::mutex> guard(m_CommitMutex);

	// Check the size
	if (m_ExternalOrderQueue.size())
	{
		// Get the load order and remove it from the queue
		_resourceOrder = m_ExternalOrderQueue[0];
		m_ExternalOrderQueue.erase(m_ExternalOrderQueue.begin() + 0);

		return true;
	}

	return false;
}

#include <fstream>
#include <iostream>

void VulkanWrapper::VWResourceLoader::LoadInternalResource(InternalResourceOrder* _resourceOrder)
{

}

void VulkanWrapper::VWResourceLoader::LoadExternalResource(ExternalResourceOrder* _resourceOrder)
{
	// Get the order resource ptr
	VWResource* resource = _resourceOrder->resourceReference->GetResource();

	// Set that we are loading this resource
	resource->SetStatus(VWResource::ResourceStatus::Loading);

	// Open the file
	std::ifstream file(_resourceOrder->resourcePath, std::fstream::binary);
	if (!file.is_open())
	{
		// Set the unknow status
		resource->SetStatus(VWResource::ResourceStatus::Unknow);

		return;
	}

	// Close the file
	file.close();

	// Set the loaded status
	resource->SetStatus(VWResource::ResourceStatus::Loaded);
}