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

	// The request type
	enum class RequestType
	{
		Unknow,					// Error
		InternalIdentifier,		// Use the resource id
		ExternalPath			// Load externally from the resource storage
	};

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
	void CreateFromId(VWResourceReference* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback);

	// Create a external new request from a given name/path
	void CreateFromPath(VWResourceReference* _resourceReference, std::string _path, std::function<void()> _wakeCallback);

	// Return the request type
	RequestType GetRequestType() { return m_RequestType; }

	// Return the request id
	uint32_t GetRequestIdentifier() { return m_ResourceId; }

	// Return the request path
	std::string GetRequestPath() { return m_ResourcePath; }

	// Return the resource reference
	VWResourceReference* GetResourceReference() { return m_ResourceReference; }

	// Return the wake callback
	std::function<void()> GetWakeCallback() { return m_WakeCallback; }

///////////////
// VARIABLES //
private: //////

	// The request type
	RequestType m_RequestType;

	// The resource ptr
	VWResourceReference* m_ResourceReference;

	// The request id (if applicable)
	uint32_t m_ResourceId;

	// The request name/path (if applicable)
	std::string m_ResourcePath;

	// The request wake callback
	std::function<void()> m_WakeCallback;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)