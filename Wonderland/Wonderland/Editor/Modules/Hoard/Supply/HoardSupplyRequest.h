////////////////////////////////////////////////////////////////////////////////
// Filename: HoardSupplyRequest.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <functional>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"
#include "..\..\Reference.h"

#include "HoardSupplyObject.h"

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

// Hoard Resource Supply Module
NamespaceBegin(Supply)

////////////////
// FORWARDING //
////////////////

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardSupplyRequest
////////////////////////////////////////////////////////////////////////////////
// typedef HoardSupplyObject ObjectType;
template <typename ObjectType>
class HoardSupplyRequest
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardSupplyRequest() {}
	~HoardSupplyRequest() {}

//////////////////
// MAIN METHODS //
public: //////////

	// Create a new request from the resource storage using an id
	void Create(Reference::Blob<ObjectType>* _resourceReference, HashedStringIdentifier _textureGroupIdentifier)
	{
		// Set the resource ptr
		m_TextureGroupReference = _resourceReference;

		// Set the id
		m_TextureGroupIdentifier = _textureGroupIdentifier;
	}

	// Return the request id
	HashedStringIdentifier GetRequestIdentifier() { return m_TextureGroupIdentifier; }

	// Return the resource reference
	Reference::Blob<ObjectType>* GetRequestReference() { return m_TextureGroupReference; }

///////////////
// VARIABLES //
private: //////

	// The texture group ptr
	Reference::Blob<ObjectType>* m_TextureGroupReference;

	// The request id (if applicable)
	HashedStringIdentifier m_TextureGroupIdentifier;
};

// Hoard Resource Supply Module
NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)