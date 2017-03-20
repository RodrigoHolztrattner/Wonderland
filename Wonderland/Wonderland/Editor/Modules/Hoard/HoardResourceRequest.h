////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResourceRequest.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <functional>

#include "..\NamespaceDefinitions.h"
#include "..\Reference.h"

#include "HoardResource.h"

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
// Class name: HoardResourceRequest
////////////////////////////////////////////////////////////////////////////////
class HoardResourceRequest
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardResourceRequest();
	~HoardResourceRequest();

//////////////////
// MAIN METHODS //
public: //////////

	// Create a new request from the resource storage using an id
	void Create(Reference::Blob<HoardResource>* _resourceReference, uint32_t _resourceId, std::function<void()> _wakeCallback, std::function<void()> _processMethod);

	// Return the request id
	uint32_t GetRequestIdentifier() { return m_ResourceId; }

	// Return the resource reference
	Reference::Blob<HoardResource>* GetResourceReference() { return m_ResourceReference; }

	// Return the wake callback
	std::function<void()> GetWakeCallback() { return m_WakeCallback; }

	// Return the process method
	std::function<void()> GetProcessMethod() { return m_ResourceProcessMethod; }

///////////////
// VARIABLES //
private: //////

	// The resource ptr
	Reference::Blob<HoardResource>* m_ResourceReference;

	// The request id
	uint32_t m_ResourceId;

	// The request wake callback
	std::function<void()> m_WakeCallback;

	// The process method
	std::function<void()> m_ResourceProcessMethod;
};

// Hoard Resource Module
NamespaceEnd(Hoard)