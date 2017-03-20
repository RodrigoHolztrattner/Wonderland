////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroupVault.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <vector>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\..\HashedString.h"

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
// Class name: VWTextureGroupVault
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupVault
{
private:

	struct TextureGroupHolder
	{
		// The texture group itself
		VWTextureGroup* textureGroup;

		// The texture group identifier
		HashedStringIdentifier resourceGroupIdentifier;
	};

public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroupVault();
	~VWTextureGroupVault();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the resource manager
	bool Initialize();

	// Check if a internal resource is currently loaded into memory
	VWTextureGroup* IsTextureGroupLoaded(HashedStringIdentifier _textureGroupIdentifier);

	// Insert a external resource into memory
	void InsertTextureGroup(VWTextureGroup* _textureGroup, HashedStringIdentifier _textureGroupIdentifier);

///////////////
// VARIABLES //
private: //////

	// Our texture group array
	std::vector<TextureGroupHolder> m_TextureGroups; //TODO: Usar um map
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)