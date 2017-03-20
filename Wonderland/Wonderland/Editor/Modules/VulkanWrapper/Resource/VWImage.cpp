////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWImage.h"
#include "..\Core\VWGraphicInstance.h"
#include "..\Core\VWCoreUtils.h"

VulkanWrapper::VWImage::VWImage()
{
	m_Image = VK_NULL_HANDLE;
	m_ImageMemory = VK_NULL_HANDLE;
	m_StaggingImage = VK_NULL_HANDLE;
	m_StaggingImageMemory = VK_NULL_HANDLE;
}

VulkanWrapper::VWImage::~VWImage()
{
}

VkCommandBuffer beginSingleTimeCommands(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = _commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(_graphicInstance->GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void endSingleTimeCommands(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(_graphicInstance->GetGraphicQueue().queue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(_graphicInstance->GetGraphicQueue().queue);

	vkFreeCommandBuffers(_graphicInstance->GetDevice(), _commandPool, 1, &commandBuffer);
}

bool hasStencilComponent(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void VulkanWrapper::VWImage::TransitionImageLayout(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	return TransitionImageLayout(_graphicInstance, _commandPool, m_Image, oldLayout, newLayout);
}

void VulkanWrapper::VWImage::TransitionImageLayout(VulkanWrapper::VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(_graphicInstance, _commandPool);

	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;

	if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (hasStencilComponent(m_Format)) {
			barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}
	else {
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	}

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
	else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
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

	endSingleTimeCommands(_graphicInstance, _commandPool, commandBuffer);
}

void VulkanWrapper::VWImage::CreateImage(VWGraphicInstance* _graphicInstance, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties)
{
	return CreateImage(_graphicInstance, _width, _height, _format, _tiling, _usage, _properties, m_Image, m_ImageView);
}

void VulkanWrapper::VWImage::CreateImage(VWGraphicInstance* _graphicInstance, uint32_t _width, uint32_t _height, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory)
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

	// Set the format
	m_Format = _format;

	if (vkCreateImage(_graphicInstance->GetDevice(), &imageInfo, nullptr, &_image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(_graphicInstance->GetDevice(), _image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = VWCoreUtils::FindMemoryType(_graphicInstance, memRequirements.memoryTypeBits, _properties);
	
	if (vkAllocateMemory(_graphicInstance->GetDevice(), &allocInfo, nullptr, &_imageMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	vkBindImageMemory(_graphicInstance->GetDevice(), _image, _imageMemory, 0);
}

void VulkanWrapper::VWImage::Update(VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, uint32_t _imageWidth, uint32_t _imageHeight, unsigned char* _imageData)
{
	VkDeviceSize imageSize = _imageWidth * _imageHeight * 4;

	VkImageSubresource subresource = {};
	subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresource.mipLevel = 0;
	subresource.arrayLayer = 0;

	VkSubresourceLayout imageLayout;
	vkGetImageSubresourceLayout(_graphicInstance->GetDevice(), m_StaggingImage, &subresource, &imageLayout);

	void* data;
	vkMapMemory(_graphicInstance->GetDevice(), m_StaggingImageMemory, 0, imageSize, 0, &data);

	if (imageLayout.rowPitch == _imageWidth * 4) {
		memcpy(data, _imageData, (size_t)imageSize);
	}
	else {
		uint8_t* dataBytes = reinterpret_cast<uint8_t*>(data);

		for (int y = 0; y < _imageHeight; y++) {
			memcpy(&dataBytes[y * imageLayout.rowPitch], &_imageData[y * _imageWidth * 4], _imageHeight * 4);
		}
	}

	vkUnmapMemory(_graphicInstance->GetDevice(), m_StaggingImageMemory);

	// Transition the image layout
	TransitionImageLayout(_graphicInstance, _commandPool, m_StaggingImage, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
	TransitionImageLayout(_graphicInstance, _commandPool, m_Image, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	CopyImage(_graphicInstance, _commandPool, m_StaggingImage, m_Image, imageSize);

	TransitionImageLayout(_graphicInstance, _commandPool, m_Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void VulkanWrapper::VWImage::CreateImageView(VWGraphicInstance* _graphicInstance, VkImageAspectFlags _aspectFlags)
{
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = m_Image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = m_Format;
	viewInfo.subresourceRange.aspectMask = _aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	if (vkCreateImageView(_graphicInstance->GetDevice(), &viewInfo, nullptr, &m_ImageView) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture image view!");
	}
}

void VulkanWrapper::VWImage::CreateImageSampler(VWGraphicInstance* _graphicInstance)
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

	if (vkCreateSampler(_graphicInstance->GetDevice(), &samplerInfo, nullptr, &m_ImageSampler) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void VulkanWrapper::VWImage::CopyImage(VWGraphicInstance* _graphicInstance, VkCommandPool _commandPool, VkImage _srcImage, VkImage _dstImage, VkDeviceSize _size)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(_graphicInstance, _commandPool);

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

	endSingleTimeCommands(_graphicInstance, _commandPool, commandBuffer);
}

void VulkanWrapper::VWImage::Release()
{

}