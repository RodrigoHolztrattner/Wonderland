////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroup.h"
#include "..\..\VWContext.h"
#include "VWTexture.h"
#include "..\..\..\LogSystem.h"

VulkanWrapper::VWTextureGroup::VWTextureGroup()
{
	// Set the initial data
	m_Status = TextureGroupStatus::Unknow;
}

VulkanWrapper::VWTextureGroup::~VWTextureGroup()
{
}

bool VulkanWrapper::VWTextureGroup::Initialize()
{
	// Set the status
	m_Status = TextureGroupStatus::Created;

	return true;
}

void VulkanWrapper::VWTextureGroup::LoadingProcess()
{
	m_Status = TextureGroupStatus::Initialized;
}

bool VulkanWrapper::VWTextureGroup::Create(VWContext* _graphicContext, VkDescriptorPool _descriptorPool, VkDescriptorSetLayout _descriptorSetLayout)
{
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = _descriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &_descriptorSetLayout;

	if (vkAllocateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), &allocInfo, &m_DescriptorSet) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate descriptor set!");
	}

	// Insert all avaliable texture ids
	for (int i = 0; i < VWTextureGroup::MaximumTexturePerGroup; i++)
	{
		m_TextureIdFreelist.push_back(i);
		m_TexturesById[i] = nullptr;
	}

	return true;
}

VulkanWrapper::VWTexture* VulkanWrapper::VWTextureGroup::FindTexture(std::string _textureName)
{
	// Check if the texture group has the target texture
	if (m_TexturesByName.find(_textureName) == m_TexturesByName.end())
	{
		return nullptr;
	}

	return m_TexturesByName[_textureName];
}

bool VulkanWrapper::VWTextureGroup::InsertTexture(VWContext* _graphicContext, VulkanWrapper::VWTexture* _texture, std::string _textureName)
{
	// Check if we have enought space avaliable
	if (m_TexturesByName.size() >= MaximumTexturePerGroup)
	{
		return false;
	}

	// Insert the texture
	m_TexturesByName[_textureName] = _texture;

	// Get a valid id for this texture
	uint32_t textureId = m_TextureIdFreelist.front();
	m_TextureIdFreelist.pop_front();

	// Set the texture slot
	m_TexturesById[textureId] = _texture;

	// Update the texture group description
	if (!UpdateDescription(_graphicContext))
	{
		return false;
	}

	return true;
}

bool VulkanWrapper::VWTextureGroup::UpdateDescription(VWContext* _graphicContext)
{
	std::vector<VkDescriptorImageInfo> imageInfos = {}; int textureIndex = 0;
	for (int i = 0; i < MaximumTexturePerGroup; i++)
	{
		// Get the current texture
		VWTexture* texture = m_TexturesById[i];

		// Check if this texture is valid
		if (texture == nullptr)
		{
			// Ignore this texture
			texture = m_TexturesById[0]; //TODO adjust the null reference
			//continue;
		}

		// Prepare the image info
		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		// imageInfo.imageView = texture->GetImageView();
		// imageInfo.sampler = texture->GetSampler();
		imageInfos.push_back(imageInfo);

		// Set the texture index
		// texture->SetId(textureIndex);

		// Increment our texture index
		textureIndex++;
	}
	
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = m_DescriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = imageInfos.size();
	descriptorWrite.pImageInfo = imageInfos.data();

	vkUpdateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), 1, &descriptorWrite, 0, nullptr);

	return true;
}