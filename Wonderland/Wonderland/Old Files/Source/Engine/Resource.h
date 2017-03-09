////////////////////////////////////////////////////////////////////////////////
// Filename: Resource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <atomic>

#include "Common\String\FHashedString.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: Resource
////////////////////////////////////////////////////////////////////////////////
class Resource
{
public:
	Resource();
	Resource(const Resource&);
	~Resource();

	// The virtual functions
	virtual bool Load() = 0;
	virtual void Update(float _time) {}
	virtual void Shutdown() = 0;

	// Return the hashed id
	FHashId GetHashId()
	{
		return m_HashId;
	}

	// Increment the number of references
	void IncrementReferences()
	{
		m_ReferenceCount++;
	}

	// Decrement the number of references
	void DecrementReferences()
	{
		m_ReferenceCount--;
	}

private:

	// The resource hashed id
	FHashId m_HashId;
	
	// The number of references
	std::atomic<unsigned int> m_ReferenceCount;
};
