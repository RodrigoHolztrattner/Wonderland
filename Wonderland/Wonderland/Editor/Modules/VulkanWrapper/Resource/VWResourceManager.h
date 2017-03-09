////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "..\..\NamespaceDefinitions.h"

#include "VWResource.h"

#include "VWResourceRequest.h"
#include "VWResourceVault.h"
#include "VWResourceCache.h"
#include "VWResourceLoader.h"

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

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWResourceManager
////////////////////////////////////////////////////////////////////////////////
class VWResourceManager
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceManager();
	~VWResourceManager();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize(uint32_t _totalWorkerThreads);

	// Return a resource sync
	// VWResource* GetResourceSync();

	// Request a resource async
	void RequestResource(VWResourceReference* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _onLoadCallback);
	void RequestResource(VWResourceReference* _resourceReference, std::string _resourcePath, std::function<void()> _onLoadCallback);

	// Process all resource request queues
	void ProcessResourceRequestQueues();

private:

	// Process the wake list
	void ProcessWakeList();

	// Process a resource request
	void ProcessResourceRequest(VWResourceRequest& _resourceRequest);
	
	// Process an internal resource
	void ProcessInternalResourceRequest(VWResourceRequest& _resourceRequest);

	// Process a external resource
	void ProcessExternalResourceRequest(VWResourceRequest& _resourceRequest);

///////////////
// VARIABLES //
private: //////

	// The total number of worker threads we are using
	uint32_t m_TotalWorkerThreads;

	// Our resource requests
	std::vector<VWResourceRequest>* m_ResourceRequests;

	// Our resource wake list
	VWResourceBase* m_ResourceWakeList;

	// Our resource vault
	VWResourceVault m_ResourceVault;

	// Our resource loader
	VWResourceLoader m_ResourceLoader;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)