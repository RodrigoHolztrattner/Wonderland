////////////////////////////////////////////////////////////////////////////////
// Filename: VWResourceIndex.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"
#include "..\..\Serialize.h"
#include "..\..\Packet\PacketString.h"

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
// Class name: VWResourceIndex
////////////////////////////////////////////////////////////////////////////////
class VWResourceIndex : public Serialize::Serializable
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWResourceIndex();
	~VWResourceIndex();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the index
	void Create(HashedStringIdentifier _groupIdentifier, const char* _resourcePath);

	// Return the identifier
	HashedStringIdentifier GetIdentifier() { return m_Identifier; }

	// Return the texture path
	Packet::PacketString* GetPath() { return &m_ResourcePath; }

	// Set the resource identifier
	void SetResourceIdentifier(uint32_t _resourceIdentifier) { m_ResourceIdentifier = _resourceIdentifier; }

	// Return the resource identifier
	uint32_t GetResourceIdentifier() { return m_ResourceIdentifier; }

	// Serialize this object
	virtual std::vector<unsigned char> Serialize() = 0;

	// Deserialize this
	virtual uint32_t Deserialize(std::vector<unsigned char>& _data, uint32_t _index) = 0;

///////////////
// VARIABLES //
protected: ////

	// Our identifier (represent the name hashed)
	HashedStringIdentifier m_Identifier;

	// Our resource path
	Packet::PacketString m_ResourcePath;

	// The resource id (this will be set using the resource path)
	uint32_t m_ResourceIdentifier;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)