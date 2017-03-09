////////////////////////////////////////////////////////////////////////////////
// Filename: VWTextureGroup.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"
#include "VWDescriptorSetCreator.h"

#include <vector>
#include <map>
#include <array>
#include <list>

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

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureGroup
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroup
{
public:

	//	static const uint32_t TextureGroupBindingLocation	= 0;
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

	// Create this texture group
	bool Create(VWContext* _graphicContext, VkDescriptorPool _descriptorPool, VkDescriptorSetLayout _descriptorSetLayout);

	// Find a texture inside this group
	VulkanWrapper::VWTexture* VWTextureGroup::FindTexture(std::string _textureName);

	// Insert a texture
	bool InsertTexture(VWContext* _graphicContext, VulkanWrapper::VWTexture* _texture, std::string _textureName);

	// Return the descriptor set
	VkDescriptorSet GetDescriptorSet() { return m_DescriptorSet; }

private:

	// Update the descriptor set
	bool UpdateDescription(VWContext* _graphicContext);

///////////////
// VARIABLES //
private: //////

	// The group descriptor set
	VkDescriptorSet m_DescriptorSet;

	 // All textures inside this group by name and texture id
	std::map<std::string, VWTexture*> m_TexturesByName;
	VWTexture* m_TexturesById[MaximumTexturePerGroup];

	// The texture id freelist
	std::list<uint32_t> m_TextureIdFreelist;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)