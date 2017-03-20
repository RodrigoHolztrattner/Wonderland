////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResourceManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "..\NamespaceDefinitions.h"
#include "..\Reference.h"

#include "HoardResource.h"

#include "HoardResourceRequest.h"
#include "HoardResourceVault.h"
#include "HoardResourceCache.h"
#include "HoardResourceLoader.h"

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

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardResourceManager
////////////////////////////////////////////////////////////////////////////////
class HoardResourceManager
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardResourceManager();
	~HoardResourceManager();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize(uint32_t _totalWorkerThreads);

	// Request a resource async
	void RequestResource(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _onLoadCallback = []() {}, std::function<void()> _processMethod = []() {});
	void RequestResource(Reference::Blob<HoardResource>* _resourceReference, std::string _resourcePath, std::function<void()> _onLoadCallback = []() {}, std::function<void()> _processMethod = []() {});

	// Process all resource request queues
	void ProcessResourceRequestQueues();

private:

	// Process the wake list
	void ProcessWakeList();

	// Process a resource request
	void ProcessResourceRequest(HoardResourceRequest& _resourceRequest);
	
	// Process an internal resource
	void ProcessInternalResourceRequest(HoardResourceRequest& _resourceRequest);

///////////////
// VARIABLES //
private: //////

	// The total number of worker threads we are using
	uint32_t m_TotalWorkerThreads;

	// Our resource requests
	std::vector<HoardResourceRequest>* m_ResourceRequests;

	// Our resource wake list
	HoardResourceBase* m_ResourceWakeList;

	// Our resource vault
	HoardResourceVault m_ResourceVault;

	// Our resource loader
	HoardResourceLoader m_ResourceLoader;
};

// Hoard Resource Module
NamespaceEnd(Hoard)