////////////////////////////////////////////////////////////////////////////////
// Filename: VWImageArray.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"
#include "..\TextureCollecion\TextureCollection.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

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
// Class name: VWImageArray
////////////////////////////////////////////////////////////////////////////////
class VWImageArray
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWImageArray();
	~VWImageArray();

//////////////////
// MAIN METHODS //
public: //////////

	// Create this image array from a given texture collection
	void CreateFromCollection(VWContext* _graphicContext, TextureCollection::TextureCollectionHeader& _collectionHeader, std::vector<TextureCollection::TextureCollectionData>& _collectionData);

	// Release this image
	void Release();

	// Return if this image was initialized
	bool IsRead();

public:

	// Return the image
	VkImage GetRawImage() { return m_Image; }

	// Return the image view
	VkImageView GetImageView() { return m_ImageView; }

	// Return the sampler
	VkSampler GetSampler() { return m_ImageSampler; }

	// Return the image width/height
	uint32_t GetWidth() { return m_Width; }
	uint32_t GetHeight() { return m_Height; }

	// Get/set the texture id
	void SetId(uint32_t _id) { m_TextureId = _id; }
	uint32_t GetId() { return m_TextureId; }

private:

	// Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
	void SetImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageAspectFlags aspectMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkImageSubresourceRange subresourceRange,
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

	// Uses a fixed sub resource layout with first mip level and layer
	void SetImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageAspectFlags aspectMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

///////////////
// VARIABLES //
private: //////

	// If this image was initialized
	bool m_Initialized;

	// Our image object and memory
	VkImage m_Image;
	VkDeviceMemory m_ImageMemory;

	// The image layout
	VkImageLayout m_ImageLayout;

	// The image view
	VkImageView m_ImageView;

	// The image sampler
	VkSampler m_ImageSampler;

	// The image width, height and layers
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_Layers;

	// The image format and usage flags
	VkFormat m_Format;
	VkImageUsageFlags m_UsageFlags;

	//

	uint32_t m_TextureId;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)