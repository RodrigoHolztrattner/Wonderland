////////////////////////////////////////////////////////////////////////////////
// Filename: VWResource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "NamespaceDefinitions.h"

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

// Reference wrapper
NamespaceBegin(Reference)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: Blob
////////////////////////////////////////////////////////////////////////////////
template <typename ObjectType /*, typename ManagerType*/ >
class Blob
{
public:

	Blob()
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
	ObjectType* GetResource()
	{
		return m_ResourcePtr;
	}

	// Access the internal resource
	ObjectType* operator->() const
	{
		//m_iterator is a map<int, MyClass>::iterator in my code.
		return m_ResourcePtr;
	}

public:

	// The ManagerType is a friend
	// friend ManagerType;

	// Validate this resource reference
	void ValidateResourceReference(ObjectType* _resourcePtr)
	{
		m_ResourcePtr = _resourcePtr;
		std::atomic_thread_fence(std::memory_order_seq_cst); // Ensure no reordering
		m_IsValid = true;
	}

private:

	// If we can use the resource reference
	bool m_IsValid;

	// Our resource ptr
	ObjectType* m_ResourcePtr;
};

// Reference wrapper
NamespaceEnd(Reference)