////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include "..\..\NamespaceDefinitions.h"

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
class VWResource;
class VWResourceReference;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWResourceLoader
////////////////////////////////////////////////////////////////////////////////
class VWResourceLoader
{
private:

	struct InternalResourceOrder
	{
		VWResourceReference* resourceReference;
		uint32_t resourceIdentifier;
	};

	struct ExternalResourceOrder
	{
		VWResourceReference* resourceReference;
		std::string resourcePath;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceLoader();
	~VWResourceLoader();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this
	bool Initialize();

	// Queue an internal resource to load
	void QueueInternalResourceLoad(VWResourceReference* _resourceReference, uint32_t _resourceIdentifier);

	// Queue an external resource to load
	void QueueExternalResourceLoad(VWResourceReference* _resourceReference, std::string _resourcePath);

	// Commit our load orders
	void CommitLoadQueues();

private:

	// Our load process aux method
	void LoadProcess();

	// Try to load an internal/external resource order
	bool TryLoadingInternalResource(InternalResourceOrder& _resourceOrder);
	bool TryLoadingExternalResource(ExternalResourceOrder& _resourceOrder);

	// Load an internal/external resource
	void LoadInternalResource(InternalResourceOrder* _resourceOrder);
	void LoadExternalResource(ExternalResourceOrder* _resourceOrder);

///////////////
// VARIABLES //
private: //////

	// Our temporary queues
	std::vector<InternalResourceOrder> m_TemporaryInternalQueue;
	std::vector<ExternalResourceOrder> m_TemporaryExternalQueue;

	// Our load queues
	std::vector<InternalResourceOrder> m_InternalOrderQueue;
	std::vector<ExternalResourceOrder> m_ExternalOrderQueue;

	// Our load thread
	std::thread m_LoadThread;

	// Our commit mutex
	std::mutex m_CommitMutex;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)