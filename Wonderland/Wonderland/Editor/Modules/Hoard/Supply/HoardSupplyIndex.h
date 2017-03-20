////////////////////////////////////////////////////////////////////////////////
// Filename: HoardSupplyIndex.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\HoardString.h"
#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"
#include "..\..\Serialize.h"

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
// Class name: HoardSupplyIndex
////////////////////////////////////////////////////////////////////////////////
class HoardSupplyIndex : public Serialize::Serializable
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HoardSupplyIndex();
	~HoardSupplyIndex();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the index
	void Create(HashedStringIdentifier _groupIdentifier, const char* _resourcePath);

	// Return the identifier
	HashedStringIdentifier GetIdentifier() { return m_Identifier; }

	// Return the texture path
	HoardString* GetPath() { return &m_ResourcePath; }

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
	HoardString m_ResourcePath;

	// The resource id (this will be set using the resource path)
	uint32_t m_ResourceIdentifier;
};

// Hoard Resource Supply Module
NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)