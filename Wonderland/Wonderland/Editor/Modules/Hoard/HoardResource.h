////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <atomic>
#include <vector>

#include "..\NamespaceDefinitions.h"
#include "HoardResourceBase.h"

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

class HoardResourceManager;
class HoardResourceLoader;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardResource
////////////////////////////////////////////////////////////////////////////////
class HoardResource : public HoardResourceBase
{
private:

	// Friends
	friend HoardResourceManager;
	friend HoardResourceLoader;

//////////////////
// CONSTRUCTORS //
private: /////////

	// Constructor / destructor
	HoardResource();
	~HoardResource();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this resource
	void Initialize();

	// Release this resource <preciso ver uma forma decente de fazer isso usando threads>
	void Release();

	// Return the byte array data
	std::vector<unsigned char>& GetByteArrayData() { return m_ByteArrayData; }

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

	// The resource byte array data
	std::vector<unsigned char> m_ByteArrayData;
};
/*
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
	HoardResource* GetResource()
	{
		return m_ResourcePtr;
	}

	// Access the internal resource
	HoardResource* operator->() const
	{
		//m_iterator is a map<int, MyClass>::iterator in my code.
		return m_ResourcePtr;
	}

protected:

	// The HoardResourceManager is a friend
	friend HoardResourceManager;

	// Validate this resource reference
	void ValidateResourceReference(HoardResource* _resourcePtr)
	{
		m_ResourcePtr = _resourcePtr;
		std::atomic_thread_fence(std::memory_order_seq_cst); // Ensure no reordering
		m_IsValid = true;
	}

private:

	// If we can use the resource reference
	bool m_IsValid;

	// Our resource ptr
	HoardResource* m_ResourcePtr;
};
*/
// Hoard Resource Module
NamespaceEnd(Hoard)