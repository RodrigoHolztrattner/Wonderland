////////////////////////////////////////////////////////////////////////////////
// Filename: VWResource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <atomic>

#include "..\..\NamespaceDefinitions.h"
#include "VWResourceBase.h"

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
class VWResourceManager;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWResource
////////////////////////////////////////////////////////////////////////////////
class VWResource : public VWResourceBase
{
private:

	// The VWResourceManager is a friend
	friend VWResourceManager;

//////////////////
// CONSTRUCTORS //
private: /////////

	// Constructor / destructor
	VWResource();
	~VWResource();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this resource
	void Initialize();

	// Release this resource <preciso ver uma forma decente de fazer isso usando threads>
	void Release();

protected:

	// Increment/decrement the reference counter
	void IncrementReferenceCount() { m_TotalReferences++; }
	void DecrementReferenceCount() { m_TotalReferences--; }

	// Return the total number of references
	uint32_t GetReferenceCount() { return m_TotalReferences; }

///////////////
// VARIABLES //
private: //////

	// The total number of references to this resource
	uint32_t m_TotalReferences;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: VWResourceReference
////////////////////////////////////////////////////////////////////////////////
class VWResourceReference
{
public:

	VWResourceReference()
	{
		// Set the initial data
		m_IsValid = false;
		m_ResourcePtr = nullptr;
	}

	// If we can use this reference
	bool IsValid()
	{
		return m_IsValid;
	}

	// Get the internal resource
	VWResource* GetResource()
	{
		return m_ResourcePtr;
	}

	// Access the internal resource
	VWResource* operator->() const
	{
		//m_iterator is a map<int, MyClass>::iterator in my code.
		return m_ResourcePtr;
	}

protected:

	// The VWResourceManager is a friend
	friend VWResourceManager;

	// Validate this resource reference
	void ValidateResourceReference(VWResource* _resourcePtr)
	{
		m_ResourcePtr = _resourcePtr;
		std::atomic_thread_fence(std::memory_order_seq_cst); // Ensure no reordering
		m_IsValid = true;
	}

private:

	// If we can use the resource reference
	bool m_IsValid;

	// Our resource ptr
	VWResource* m_ResourcePtr;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)