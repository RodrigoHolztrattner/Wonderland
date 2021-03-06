////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupIndex.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\HoardResourceIndex.h"

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
// Class name: VWTextureGroupIndex
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupIndex : public HoardResourceIndex
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupIndex();
	~VWTextureGroupIndex();

//////////////////
// MAIN METHODS //
public: //////////

	// Serialize this object
	std::vector<unsigned char> Serialize();

	// Deserialize this
	uint32_t Deserialize(std::vector<unsigned char>& _data, uint32_t _index);

///////////////
// VARIABLES //
private: //////

};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)