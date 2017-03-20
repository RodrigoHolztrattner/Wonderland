////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWImage.h"
#include "VWContext.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

VulkanWrapper::VWTexture::VWTexture()
{
	m_Image = VK_NULL_HANDLE;
	m_ImageMemory = VK_NULL_HANDLE;
	m_StaggingImage = VK_NULL_HANDLE;
	m_StaggingImageMemory = VK_NULL_HANDLE;
	//	m_BufferSize = 0;
	m_Initialized = false;
}

VulkanWrapper::VWTexture::~VWTexture()
{
}

VkCommandBuffer beginSingleTimeCommands(VulkanWrapper::VWContext* _graphicContext, VkCommandPool _commandPool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = _commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(_graphicContext->GetGraphicInstance()->GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void endSingleTimeCommands(VulkanWrapper::VWContext* _graphicContext, VkCommandPool _commandPool, VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(_graphicContext->GetGraphicInstance()->GetGraphicQueue().queue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(_graphicContext->GetGraphicInstance()->GetGraphicQueue().queue);

	vkFreeCommandBuffers(_graphicContext->GetGraphicInstance()->GetDevice(), _commandPool, 1, &commandBuffer);
}

void transitionImageLayout(VulkanWrapper::VWContext* _graphicContext, VkCommandPool _commandPool, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(_graphicContext, _commandPool);

	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	if (oldLayout == VK_IMAGE_LAYOUT_PREINITIALIZED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_PREINITIALIZED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	}
	else {
		throw std::invalid_argument("unsupported layout transition!");
	}

	vkCmdPipelineBarrier(
		commandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

	endSingleTimeCommands(_graphicContext, _commandPool, commandBuffer);
}

void VulkanWrapper::VWTexture::Create(VWContext* _graphicContext, VkCommandPool _commandPool, char* _filename)
{
	CreateEx(_graphicContext, _commandPool, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT, _filename);
}

void VulkanWrapper::VWTexture::CreateEx(VWContext* _graphicContext, VkCommandPool _commandPool, VkFormat _format, VkImageUsageFlags _usage, char* _filename)
{
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(_filename, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	// Check if we loaded correctly
	if (!pixels)
	{
		throw std::runtime_error("failed to load texture image!");
	}

	// Set the width and height
	m_Width = texWidth;
	m_Height = texHeight;

	// Set the configuration data
	m_Format = _format;
	m_UsageFlags = _usage;

	// Create the texture image
	CreateImage(_graphicContext, texWidth, texHeight, m_Format, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_StaggingImage, m_StaggingImageMemory);
	CreateImage(_graphicContext, texWidth, texHeight, m_Format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | m_UsageFlags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Image, m_ImageMemory);

	//
	Update(_graphicContext, _commandPool, m_Width, m_Height, pixels);

	stbi_image_free(pixels);

	CreateImageView(_graphicContext);
	CreateImageSampler(_graphicContext);
}

void VulkanWrapper::VWTexture::CreateImage(VWContext* _graphicContext, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory)
{
	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = _width;
	imageInfo.extent.height = _height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = _format;
	imageInfo.tiling = _tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	imageInfo.usage = _usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateImage(_graphicContext->GetGraphicInstance()->GetDevice(), &imageInfo, nullptr, &_image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(_graphicContext->GetGraphicInstance()->GetDevice(), _image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = _graphicContext->FindMemoryType(memRequirements.memoryTypeBits, _properties);

	if (vkAllocateMemory(_graphicContext->GetGraphicInstance()->GetDevice(), &allocInfo, nullptr, &_imageMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	vkBindImageMemory(_graphicContext->GetGraphicInstance()->GetDevice(), _image, _imageMemory, 0);
}

void VulkanWrapper::VWTexture::Update(VWContext* _graphicContext, VkCommandPool _commandPool, uint32_t _imageWidth, uint32_t _imageHeight, unsigned char* _imageData)
{
	VkDeviceSize imageSize = _imageWidth * _imageHeight * 4;

	VkImageSubresource subresource = {};
	subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresource.mipLevel = 0;
	subresource.arrayLayer = 0;

	VkSubresourceLayout imageLayout;
	vkGetImageSubresourceLayout(_graphicContext->GetGraphicInstance()->GetDevice(), m_StaggingImage, &subresource, &imageLayout);

	void* data;
	vkMapMemory(_graphicContext->GetGraphicInstance()->GetDevice(), m_StaggingImageMemory, 0, imageSize, 0, &data);

	if (imageLayout.rowPitch == _imageWidth * 4) {
		memcpy(data, _imageData, (size_t)imageSize);
	}
	else {
		uint8_t* dataBytes = reinterpret_cast<uint8_t*>(data);

		for (int y = 0; y < _imageHeight; y++) {
			memcpy(&dataBytes[y * imageLayout.rowPitch], &_imageData[y * _imageWidth * 4], _imageHeight * 4);
		}
	}

	vkUnmapMemory(_graphicContext->GetGraphicInstance()->GetDevice(), m_StaggingImageMemory);

	// Transition the image layout
	transitionImageLayout(_graphicContext, _commandPool, m_StaggingImage, m_Format, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
	transitionImageLayout(_graphicContext, _commandPool, m_Image, m_Format, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	CopyImage(_graphicContext, _commandPool, m_StaggingImage, m_Image, imageSize);

	transitionImageLayout(_graphicContext, _commandPool, m_Image, m_Format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void VulkanWrapper::VWTexture::CreateImageView(VWContext* _graphicContext)
{
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_Image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = m_Format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	if (vkCreateImageView(_graphicContext->GetGraphicInstance()->GetDevice(), &viewInfo, nullptr, &m_ImageView) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture image view!");
	}
}

void VulkanWrapper::VWTexture::CreateImageSampler(VWContext* _graphicContext)
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	if (vkCreateSampler(_graphicContext->GetGraphicInstance()->GetDevice(), &samplerInfo, nullptr, &m_ImageSampler) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void VulkanWrapper::VWTexture::CopyImage(VWContext* _graphicContext, VkCommandPool _commandPool, VkImage _srcImage, VkImage _dstImage, VkDeviceSize _size)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(_graphicContext, _commandPool);

	VkImageSubresourceLayers subResource = {};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subResource.baseArrayLayer = 0;
	subResource.mipLevel = 0;
	subResource.layerCount = 1;

	VkImageCopy region = {};
	region.srcSubresource = subResource;
	region.dstSubresource = subResource;
	region.srcOffset = { 0, 0, 0 };
	region.dstOffset = { 0, 0, 0 };
	region.extent.width = m_Width;
	region.extent.height = m_Height;
	region.extent.depth = 1;

	vkCmdCopyImage(
		commandBuffer,
		_srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		_dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1, &region
	);

	endSingleTimeCommands(_graphicContext, _commandPool, commandBuffer);
}

void VulkanWrapper::VWTexture::Release()
{

}

bool VulkanWrapper::VWTexture::IsRead()
{
	return m_Initialized;
}