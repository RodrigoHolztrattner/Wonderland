////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResourceLoader.h
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

#include "..\NamespaceDefinitions.h"
#include "..\Reference.h"

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

class HoardResource;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardResourceLoader
////////////////////////////////////////////////////////////////////////////////
class HoardResourceLoader
{
private:

	struct ResourceOrder
	{
		Reference::Blob<HoardResource>* resourceReference;
		uint32_t resourceIdentifier;
		std::function<void()> resourceProcessMethod;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardResourceLoader();
	~HoardResourceLoader();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this
	bool Initialize();

	// Queue an internal resource to load
	void QueueResourceLoad(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceIdentifier, std::function<void()> _processResourceMethod);

	// Commit our load orders
	void CommitLoadQueues();

private:

	// Our load process aux method
	void LoadProcess();

	// Try to load an internal/external resource order
	bool TryLoadingResource(ResourceOrder& _resourceOrder);

	// Load an internal/external resource
	void LoadResource(ResourceOrder* _resourceOrder);

///////////////
// VARIABLES //
private: //////

	// Our temporary queues
	std::vector<ResourceOrder> m_TemporaryQueue;

	// Our load queues
	std::vector<ResourceOrder> m_OrderQueue;

	// Our load thread
	std::thread m_LoadThread;

	// Our commit mutex
	std::mutex m_CommitMutex;
};

// Hoard Resource Module
NamespaceEnd(Hoard)