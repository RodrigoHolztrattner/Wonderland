////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWTextureGroup.h"
#include "..\..\Context\VWContext.h"
#include "..\..\..\LogSystem.h"
#include "..\..\..\TextureCollecion\TextureCollectionUnpacker.h"

VulkanWrapper::VWTextureGroup::VWTextureGroup()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWTextureGroup::~VWTextureGroup()
{
}

bool VulkanWrapper::VWTextureGroup::CreateDescriptorSet(VWContext* _graphicContext, VkDescriptorPool _descriptorPool, VkDescriptorSetLayout _descriptorSetLayout)
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

	return true;
}

bool VulkanWrapper::VWTextureGroup::ProcessResource(VWContext* _graphicContext)
{
	// Get the resource reference
	Reference::Blob<Hoard::HoardResource>* resourceReference = GetResourceReference();

	// Get the resource itself
	Hoard::HoardResource* resource = resourceReference->GetResource();

	// Get the resource byte array
	std::vector<unsigned char>& byteArray = resource->GetByteArrayData();

	// Prepare to unpack the texture group
	TextureCollection::TextureCollectionUnpacker textureCollectionUnpacker;

	// Unpack the texture collection
	bool unpackResult;
	std::vector<TextureCollection::TextureCollectionData> unpackedTextures = textureCollectionUnpacker.UnpackCollection(byteArray, unpackResult);

	// Check if the unpack was sucessfull
	if (!unpackResult)
	{
		// Error unpacking the texture
		return false;
	}

	// Get the header data
	TextureCollection::TextureCollectionHeader& collectionHeader = textureCollectionUnpacker.GetCollectionHeader();

	// Set the texture group identificator
	m_TextureGroupIdentificator = HashedString(collectionHeader.collectionName.GetString()).Hash();

	// Create the image from the collection
	m_Image.CreateFromCollection(_graphicContext, collectionHeader, unpackedTextures);

	// Prepare the image info
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = m_Image.GetImageView();
	imageInfo.sampler = m_Image.GetSampler();

	// Prepare the descriptor write data
	VkDescriptorImageInfo imageInfos[] = { imageInfo };
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = m_DescriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pImageInfo = imageInfos;

	// Update the descriptor set
	vkUpdateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), 1, &descriptorWrite, 0, nullptr);

	// Insert all texture names into the map
	for (int i = 0; i<unpackedTextures.size(); i++)
	{
		// Get the current texture
		TextureCollection::TextureCollectionData& textureData = unpackedTextures[i];

		// Hash the texture name
		HashedStringIdentifier hashedTextureName = HashedString(textureData.name.GetString()).Hash();

		// Insert into the map
		m_TextureNameMap[hashedTextureName] = i;
	}

	return true;
}

uint32_t VulkanWrapper::VWTextureGroup::FindTextureIndex(const char* _textureName)
{
	// Hash the name
	HashedStringIdentifier hashedTextureName = HashedString(_textureName).Hash();

	// Check if the given texture exist
	if (m_TextureNameMap.find(hashedTextureName) == m_TextureNameMap.end())
	{
		// Error, there is no texture with the given name
		return -1;
	}

	return m_TextureNameMap[hashedTextureName];
}

bool VulkanWrapper::VWTextureGroup::IsValid()
{
	// Check our current status
	if (GetStatus() != Hoard::Supply::Object::Status::Initialized)
	{
		return false;
	}

	// Get the resource reference
	Reference::Blob<Hoard::HoardResource>* resourceReference = GetResourceReference();
	if (!resourceReference->IsValid())
	{
		return false;
	}

	// Get the resource itself
	Hoard::HoardResource* resource = resourceReference->GetResource();
	if (resource->GetStatus() != Hoard::Resource::ResourceStatus::Initialized)
	{
		return false;
	}

	return true;
}