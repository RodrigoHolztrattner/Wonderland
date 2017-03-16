////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupRequest.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <functional>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\..\HashedString.h"
#include "..\..\..\Reference.h"

#include "VWTextureGroup.h"

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
// Class name: VWTextureGroupRequest
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupRequest
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupRequest();
	~VWTextureGroupRequest();

//////////////////
// MAIN METHODS //
public: //////////

	// Create a new request from the resource storage using an id
	void Create(Reference::Blob<VWTextureGroup>* _resourceReference, HashedStringIdentifier _textureGroupIdentifier);

	// Return the request id
	HashedStringIdentifier GetRequestIdentifier() { return m_TextureGroupIdentifier; }

	// Return the resource reference
	Reference::Blob<VWTextureGroup>* GetRequestReference() { return m_TextureGroupReference; }

///////////////
// VARIABLES //
private: //////

	// The texture group ptr
	Reference::Blob<VWTextureGroup>* m_TextureGroupReference;

	// The request id (if applicable)
	HashedStringIdentifier m_TextureGroupIdentifier;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)