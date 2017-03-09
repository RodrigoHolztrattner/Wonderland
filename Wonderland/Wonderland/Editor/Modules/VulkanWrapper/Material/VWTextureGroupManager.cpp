////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroupManager.h"
#include "..\VWContext.h"
#include "VWTexture.h"
#include "..\..\LogSystem.h"

VulkanWrapper::VWTextureGroupManager::VWTextureGroupManager()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroupManager::~VWTextureGroupManager()
{
}

bool VulkanWrapper::VWTextureGroupManager::Initialize(VWContext* _graphicContext)
{
	// Add our layout descriptors
	AddDescriptorSetLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VWTextureGroup::MaximumTexturePerGroup, VK_SHADER_STAGE_FRAGMENT_BIT);

	// Create the descriptor pool
	CreateDescriptorPool(_graphicContext, VWTextureGroup::MaximumTextureGroups);

	// Create the set layout
	CreateDescriptorSetLayout(_graphicContext);

	return true;
}

void VulkanWrapper::VWTextureGroupManager::Release()
{

}

VulkanWrapper::VWTexture* VulkanWrapper::VWTextureGroupManager::GetTexture(VWContext* _graphicContext, std::string _textureName, std::string _textureGroup, VkCommandPool _commandPool)
{
	// Check if the texture group exists
	VulkanWrapper::VWTextureGroup* textureGroup = FindTextureGroup(_textureGroup);
	if (textureGroup == nullptr)
	{
		// Create a new texture group
		textureGroup = &m_TextureGroups[_textureGroup];
		if(!textureGroup->Create(_graphicContext, m_DescriptorPool, m_DescriptorSetLayout))
		{
			throw std::runtime_error("failed to create texture group!");
		}
	}

	// Check if the texture already exists
	VWTexture* texture = textureGroup->FindTexture(_textureName);
	if (texture == nullptr)
	{
		// Create a new texture
		texture = CreateTexture(_graphicContext, _textureName, _commandPool);
		if(texture == nullptr)
		{
			throw std::runtime_error("failed to create texture!");
		}

		// Insert the created texture into the group
		if (!textureGroup->InsertTexture(_graphicContext, texture, _textureName))
		{
			throw std::runtime_error("failed to insert texture into group!");
		}
	}

	return texture;
}

VulkanWrapper::VWTextureGroup* VulkanWrapper::VWTextureGroupManager::FindTextureGroup(std::string _textureGroup)
{
	// Check if the texture group exist
	if (m_TextureGroups.find(_textureGroup) == m_TextureGroups.end())
	{
		return nullptr;
	}

	return &m_TextureGroups[_textureGroup];
}

VulkanWrapper::VWTexture* VulkanWrapper::VWTextureGroupManager::CreateTexture(VWContext* _graphicContext, std::string _textureName, VkCommandPool _commandPool)
{
	VWTexture* newTexture = new VWTexture();

	newTexture->Create(_graphicContext, _commandPool, (char*)_textureName.c_str()); //TODO: Use a better method (creation command)

	return newTexture;
}