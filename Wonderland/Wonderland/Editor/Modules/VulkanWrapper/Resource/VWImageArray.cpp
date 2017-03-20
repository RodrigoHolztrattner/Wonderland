////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWImageArray.h"
#include "..\Context\VWContext.h"

// #define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

VulkanWrapper::VWImageArray::VWImageArray()
{
	m_Image = VK_NULL_HANDLE;
	m_ImageMemory = VK_NULL_HANDLE;
	m_Initialized = false;
}

VulkanWrapper::VWImageArray::~VWImageArray()
{
}


VkCommandBuffer BeginSingleTimeCommands(VulkanWrapper::VWContext* _graphicContext)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = _graphicContext->GetGraphicInstance()->GetCommandPool();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(_graphicContext->GetGraphicInstance()->GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void EndSingleTimeCommands(VulkanWrapper::VWContext* _graphicContext, VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(_graphicContext->GetGraphicInstance()->GetGraphicQueue().queue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(_graphicContext->GetGraphicInstance()->GetGraphicQueue().queue);

	vkFreeCommandBuffers(_graphicContext->GetGraphicInstance()->GetDevice(), _graphicContext->GetGraphicInstance()->GetCommandPool(), 1, &commandBuffer);
}

void VulkanWrapper::VWImageArray::CreateFromCollection(VWContext* _graphicContext, TextureCollection::TextureCollectionHeader& _collectionHeader, std::vector<TextureCollection::TextureCollectionData>& _collectionData)
{
	// Set the width and height
	m_Width = _collectionHeader.width;
	m_Height = _collectionHeader.height;

	// The total number of layers
	m_Layers = _collectionData.size();

	// Set the format
	m_Format = VK_FORMAT_R8G8B8A8_UNORM; //TODO: Definir qual é o modelo de compressão suportado! -> https://github.com/SaschaWillems/Vulkan/blob/master/texturearray/texturearray.cpp

	// Get the graphic instance
	VWGraphicInstance* graphicInstance = _graphicContext->GetGraphicInstance();

	// Get the device
	VkDevice device = graphicInstance->GetDevice();

	//
	//
	//

	VkMemoryRequirements memReqs;

	// Create a host-visible staging buffer that contains the raw image data
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingMemory;

	// This buffer is used as a transfer source for the buffer copy
	VkBufferCreateInfo bufferCreateInfo = {};
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = m_Width * m_Height * m_Layers * 4;
	bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	vkCreateBuffer(device, &bufferCreateInfo, nullptr, &stagingBuffer);

	// Get memory requirements for the staging buffer (alignment, memory type bits)
	vkGetBufferMemoryRequirements(device, stagingBuffer, &memReqs);

	// Get memory type index for a host visible buffer
	VkMemoryAllocateInfo memAllocInfo = {};
	memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllocInfo.allocationSize = memReqs.size;
	memAllocInfo.memoryTypeIndex = _graphicContext->FindMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	vkAllocateMemory(device, &memAllocInfo, nullptr, &stagingMemory);
	vkBindBufferMemory(device, stagingBuffer, stagingMemory, 0);

	//

	// Copy texture data into staging buffer
	unsigned char *data;
	vkMapMemory(device, stagingMemory, 0, memReqs.size, 0, (void **)&data);

	// Copy each texture
	uint32_t byteLocation = 0;
	for (int i = 0; i < _collectionData.size(); i++)
	{
		memcpy(&data[byteLocation], _collectionData[i].data, m_Width * m_Height * 4);
		byteLocation += m_Width * m_Height * 4;
	}

	vkUnmapMemory(device, stagingMemory);

	// Setup buffer copy regions for array layers
	std::vector<VkBufferImageCopy> bufferCopyRegions;
	uint32_t offset = 0;

	VkBufferImageCopy bufferCopyRegion = {};
	bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	bufferCopyRegion.imageSubresource.mipLevel = 0;
	bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
	bufferCopyRegion.imageSubresource.layerCount = m_Layers;
	bufferCopyRegion.imageExtent.width = m_Width;
	bufferCopyRegion.imageExtent.height = m_Height;
	bufferCopyRegion.imageExtent.depth = 1;
	bufferCopyRegion.bufferOffset = offset;

	bufferCopyRegions.push_back(bufferCopyRegion);

	//
	//
	//

	// Create optimal tiled target image
	VkImageCreateInfo imageCreateInfo = {};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	imageCreateInfo.format = m_Format;
	imageCreateInfo.mipLevels = 1;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageCreateInfo.extent = { m_Width, m_Height, 1 };
	imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageCreateInfo.arrayLayers = m_Layers;

	vkCreateImage(device, &imageCreateInfo, nullptr, &m_Image);

	vkGetImageMemoryRequirements(device, m_Image, &memReqs);

	memAllocInfo = {};
	memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllocInfo.allocationSize = memReqs.size;
	memAllocInfo.memoryTypeIndex = _graphicContext->FindMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	vkAllocateMemory(device, &memAllocInfo, nullptr, &m_ImageMemory);
	vkBindImageMemory(device, m_Image, m_ImageMemory, 0);

	//
	
	VkCommandBuffer copyCmd = BeginSingleTimeCommands(_graphicContext);

	// Image barrier for optimal image (target)
	// Set initial layout for all array layers (faces) of the optimal (target) tiled texture
	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = 1;
	subresourceRange.layerCount = m_Layers;

	SetImageLayout(copyCmd, m_Image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, subresourceRange);

	// Copy the cube map faces from the staging buffer to the optimal tiled image
	vkCmdCopyBufferToImage(copyCmd, stagingBuffer, m_Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, bufferCopyRegions.size(), bufferCopyRegions.data());

	// Change texture image layout to shader read after all faces have been copied
	m_ImageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	SetImageLayout(copyCmd, m_Image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_ImageLayout, subresourceRange);

	EndSingleTimeCommands(_graphicContext, copyCmd);

	//

	// Create sampler
	VkSamplerCreateInfo sampler = {};
	sampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	sampler.magFilter = VK_FILTER_LINEAR;
	sampler.minFilter = VK_FILTER_LINEAR;
	sampler.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	sampler.addressModeV = sampler.addressModeU;
	sampler.addressModeW = sampler.addressModeU;
	sampler.anisotropyEnable = VK_TRUE;
	sampler.unnormalizedCoordinates = VK_FALSE;
	sampler.compareEnable = VK_FALSE;
	sampler.mipLodBias = 0.0f;
	sampler.maxAnisotropy = 16;
	sampler.compareOp = VK_COMPARE_OP_NEVER;
	sampler.minLod = 0.0f;
	sampler.maxLod = 0.0f;
	sampler.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	vkCreateSampler(device, &sampler, nullptr, &m_ImageSampler);

	// Create image view
	VkImageViewCreateInfo view = {};
	view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	view.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
	view.format = m_Format;
	view.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
	view.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
	view.subresourceRange.layerCount = m_Layers;
	view.image = m_Image;
	vkCreateImageView(device, &view, nullptr, &m_ImageView);

	// Clean up staging resources
	vkFreeMemory(device, stagingMemory, nullptr);
	vkDestroyBuffer(device, stagingBuffer, nullptr);
}

void VulkanWrapper::VWImageArray::Release()
{

}

bool VulkanWrapper::VWImageArray::IsRead()
{
	return m_Initialized;
}

void VulkanWrapper::VWImageArray::SetImageLayout(
	VkCommandBuffer cmdbuffer,
	VkImage image,
	VkImageAspectFlags aspectMask,
	VkImageLayout oldImageLayout,
	VkImageLayout newImageLayout,
	VkImageSubresourceRange subresourceRange,
	VkPipelineStageFlags srcStageMask,
	VkPipelineStageFlags dstStageMask)
{
	// Create an image barrier object
	VkImageMemoryBarrier imageMemoryBarrier = {};
	imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	imageMemoryBarrier.oldLayout = oldImageLayout;
	imageMemoryBarrier.newLayout = newImageLayout;
	imageMemoryBarrier.image = image;
	imageMemoryBarrier.subresourceRange = subresourceRange;
	
	// Source layouts (old)
	// Source access mask controls actions that have to be finished on the old layout
	// before it will be transitioned to the new layout
	switch (oldImageLayout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		// Image layout is undefined (or does not matter)
		// Only valid as initial layout
		// No flags required, listed only for completeness
		imageMemoryBarrier.srcAccessMask = 0;
		break;

	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		// Image is preinitialized
		// Only valid as initial layout for linear images, preserves memory contents
		// Make sure host writes have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		// Image is a color attachment
		// Make sure any writes to the color buffer have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		// Image is a depth/stencil attachment
		// Make sure any writes to the depth/stencil buffer have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		// Image is a transfer source 
		// Make sure any reads from the image have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		// Image is a transfer destination
		// Make sure any writes to the image have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		// Image is read by a shader
		// Make sure any shader reads from the image have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		break;
	}

	// Target layouts (new)
	// Destination access mask controls the dependency for the new image layout
	switch (newImageLayout)
	{
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		// Image will be used as a transfer destination
		// Make sure any writes to the image have been finished
		imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		// Image will be used as a transfer source
		// Make sure any reads from and writes to the image have been finished
		imageMemoryBarrier.srcAccessMask = imageMemoryBarrier.srcAccessMask | VK_ACCESS_TRANSFER_READ_BIT;
		imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		// Image will be used as a color attachment
		// Make sure any writes to the color buffer have been finished
		imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		// Image layout will be used as a depth/stencil attachment
		// Make sure any writes to depth/stencil buffer have been finished
		imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		// Image will be read in a shader (sampler, input attachment)
		// Make sure any writes to the image have been finished
		if (imageMemoryBarrier.srcAccessMask == 0)
		{
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
		}
		imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		break;
	}

	// Put barrier inside setup command buffer
	vkCmdPipelineBarrier(
		cmdbuffer,
		srcStageMask,
		dstStageMask,
		0,
		0, nullptr,
		0, nullptr,
		1, &imageMemoryBarrier);
}

// Fixed sub resource on first mip level and layer
void VulkanWrapper::VWImageArray::SetImageLayout(
	VkCommandBuffer cmdbuffer,
	VkImage image,
	VkImageAspectFlags aspectMask,
	VkImageLayout oldImageLayout,
	VkImageLayout newImageLayout,
	VkPipelineStageFlags srcStageMask,
	VkPipelineStageFlags dstStageMask)
{
	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = aspectMask;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = 1;
	subresourceRange.layerCount = 1;
	SetImageLayout(cmdbuffer, image, aspectMask, oldImageLayout, newImageLayout, subresourceRange);
}