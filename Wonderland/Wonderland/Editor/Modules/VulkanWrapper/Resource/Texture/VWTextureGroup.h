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
#include "..\VWResource.h"

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
class VWTextureGroup
{
public:

	enum class TextureGroupStatus
	{
		Unknow,
		Created,
		Loading,
		Loaded,
		Initialized
	};

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

	// Initialize this texture group
	bool Initialize();

	// The loading process
	void LoadingProcess();

	// Create this texture group
	bool Create(VWContext* _graphicContext, VkDescriptorPool _descriptorPool, VkDescriptorSetLayout _descriptorSetLayout);

	// Find a texture inside this group
	VulkanWrapper::VWTexture* VWTextureGroup::FindTexture(std::string _textureName);

	// Insert a texture
	bool InsertTexture(VWContext* _graphicContext, VulkanWrapper::VWTexture* _texture, std::string _textureName);

	// Return the descriptor set
	VkDescriptorSet GetDescriptorSet() { return m_DescriptorSet; }

	// Return the status
	TextureGroupStatus GetStatus() { return m_Status; }

	// Return the resource reference
	Reference::Blob<VulkanWrapper::VWResource>* GetResourceReference() { return &m_ResourceReference; }

private:

	// Update the descriptor set
	bool UpdateDescription(VWContext* _graphicContext);

///////////////
// VARIABLES //
private: //////

	// The status
	TextureGroupStatus m_Status;

	// The resource reference
	Reference::Blob<VulkanWrapper::VWResource> m_ResourceReference;

	// The group descriptor set
	VkDescriptorSet m_DescriptorSet;

	 // All textures inside this group by name and texture id
	std::map<std::string, VWTexture*> m_TexturesByName;
	VWTexture* m_TexturesById[MaximumTexturePerGroup];

	// The texture id freelist
	std::list<uint32_t> m_TextureIdFreelist;
};
/*
////////////////////////////////////////////////////////////////////////////////
// Class name: VWTextureGroupReference
////////////////////////////////////////////////////////////////////////////////
class VWTextureGroupReference
{
public:

	VWTextureGroupReference()
	{
		// Set the initial data
		m_IsValid = false;
		m_TextureGroupPtr = nullptr;
	}

	// If we can use this reference
	bool IsValid()
	{
		return m_IsValid;
	}

	// Get the internal resource
	VWTextureGroup* GetGroup()
	{
		return m_TextureGroupPtr;
	}

	// Access the internal texture group
	VWTextureGroup* operator->() const
	{
		return m_TextureGroupPtr;
	}

protected:

	// The VWResourceManager is a friend
	friend VWTextureGroupManager;

	// Validate this resource reference
	void ValidateResourceReference(VWTextureGroup* _textureGroupPtr)
	{
		m_TextureGroupPtr = _textureGroupPtr;
		std::atomic_thread_fence(std::memory_order_seq_cst); // Ensure no reordering
		m_IsValid = true;
	}

private:

	// If we can use the resource reference
	bool m_IsValid;

	// Our resource ptr
	VWTextureGroup* m_TextureGroupPtr;
};
*/
// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)