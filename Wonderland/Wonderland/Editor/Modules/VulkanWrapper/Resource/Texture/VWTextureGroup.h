////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroup.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\..\NamespaceDefinitions.h"
#include "..\..\Material\VWDescriptorSetCreator.h"
#include "..\..\..\Reference.h"
#include "..\..\..\HashedString.h"
#include "..\..\..\Hoard\Hoard.h"
#include "..\..\VWImageArray.h"

#include <vector>
#include <map>
#include <array>
#include <list>
#include <atomic>

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
class VWTexture;
class VWTextureGroupManager;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureGroup
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroup : public Hoard::Supply::Object
{
public:

	// Static const uint32_t TextureGroupBindingLocation	= 0;
	static const uint32_t MaximumTexturePerGroup = 76;
	static const uint32_t MaximumTextureGroups = 1024;

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWTextureGroup();
	~VWTextureGroup();

//////////////////
// MAIN METHODS //
public: //////////

	// Create the descriptor set
	bool CreateDescriptorSet(VWContext* _graphicContext, VkDescriptorPool _descriptorPool, VkDescriptorSetLayout _descriptorSetLayout);

	// Process the internal resource
	bool ProcessResource(VWContext* _graphicContext);

	// Return the descriptor set
	VkDescriptorSet GetDescriptorSet() { return m_DescriptorSet; }

	// Return the total number of textures
	uint32_t GetTotalTextures() { return m_TextureNameMap.size(); }

	// Return the texture group identificator
	HashedStringIdentifier GetTextureGroupIdentificator() { return m_TextureGroupIdentificator; }

	// Check if this object is valid
	bool IsValid() override;

protected:

	// Texture is a friend class
	friend VWTexture;

	// Find a texture inside this group
	uint32_t VWTextureGroup::FindTextureIndex(const char* _textureName);

///////////////
// VARIABLES //
private: //////

	// The image object
	VWImageArray m_Image;

	// The texture group identificator
	HashedStringIdentifier m_TextureGroupIdentificator;

	// The group descriptor set
	VkDescriptorSet m_DescriptorSet;

	// The texture name map
	std::map<HashedStringIdentifier, uint32_t> m_TextureNameMap;
};

typedef Reference::Blob<VWTextureGroup> VWTextureGroupReference;

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)