////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceRequest.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\Reference.h"

#include "VWResource.h"

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
// Class name: VWResourceRequest
////////////////////////////////////////////////////////////////////////////////
class VWResourceRequest
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceRequest();
	~VWResourceRequest();

//////////////////
// MAIN METHODS //
public: //////////

	// Create a new request from the resource storage using an id
	void Create(Reference::Blob<VWResource>* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback, std::function<void()> _processMethod);

	// Return the request id
	uint32_t GetRequestIdentifier() { return m_ResourceId; }

	// Return the resource reference
	Reference::Blob<VWResource>* GetResourceReference() { return m_ResourceReference; }

	// Return the wake callback
	std::function<void()> GetWakeCallback() { return m_WakeCallback; }

	// Return the process method
	std::function<void()> GetProcessMethod() { return m_ResourceProcessMethod; }

///////////////
// VARIABLES //
private: //////

	// The resource ptr
	Reference::Blob<VWResource>* m_ResourceReference;

	// The request id
	uint32_t m_ResourceId;

	// The request wake callback
	std::function<void()> m_WakeCallback;

	// The process method
	std::function<void()> m_ResourceProcessMethod;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)