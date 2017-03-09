////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWBufferClear.h"
#include "VWGraphicAdapter.h"
#include "VWSwapChain.h"
#include "VWGraphicInstance.h"

VulkanWrapper::VWBufferClear::VWBufferClear()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWBufferClear::~VWBufferClear()
{
}

bool VulkanWrapper::VWBufferClear::Initialize()
{
	return true;
}

void VulkanWrapper::VWBufferClear::CreateCommandBuffers(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain)
{
	// Get the swap chain images
	const std::vector<VkImageView>& swapChainImageViews = _swapChain->GetImageViews();
	const std::vector<VkImage>& swapChainImages = _swapChain->GetImages();

	if (commandBuffers.size() > 0)
	{
		vkFreeCommandBuffers(_graphicInstance->GetDevice(), commandPool, commandBuffers.size(), commandBuffers.data());
	}

	commandBuffers.resize(swapChainImages.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(_graphicInstance->GetDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	VkClearColorValue clear_color = 
	{ 0.0f, 0.0f, 0.0f, 1.0f };

	VkImageSubresourceRange image_subresource_range =
	{
		VK_IMAGE_ASPECT_COLOR_BIT,                    // VkImageAspectFlags                     aspectMask	
		0,                                            // uint32_t                               baseMipLevel	
		1,                                            // uint32_t                               levelCount	
		0,                                            // uint32_t                               baseArrayLayer	
		1                                             // uint32_t                               layerCount
	};

	for (size_t i = 0; i < commandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		
		VkImageMemoryBarrier barrier_from_present_to_clear =
		{
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,     // VkStructureType                        sType
			nullptr,                                    // const void                            *pNext
			0,                  // VkAccessFlags                          srcAccessMask
			VK_ACCESS_TRANSFER_WRITE_BIT,               // VkAccessFlags                          dstAccessMask
			VK_IMAGE_LAYOUT_UNDEFINED,                  // VkImageLayout                          oldLayout
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,       // VkImageLayout                          newLayout
			_graphicInstance->GetPresentQueue().index,             // uint32_t                               srcQueueFamilyIndex
			_graphicInstance->GetPresentQueue().index,             // uint32_t                               dstQueueFamilyIndex
			swapChainImages[i],                       // VkImage                                image
			image_subresource_range                     // VkImageSubresourceRange                subresourceRange
		};

		VkImageMemoryBarrier barrier_from_clear_to_present =
		{
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,     // VkStructureType                        sType
			nullptr,                                    // const void                            *pNext
			VK_ACCESS_TRANSFER_WRITE_BIT,               // VkAccessFlags                          srcAccessMask
			VK_ACCESS_MEMORY_READ_BIT,                  // VkAccessFlags                          dstAccessMask
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,       // VkImageLayout                          oldLayout
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,            // VkImageLayout                          newLayout
			_graphicInstance->GetPresentQueue().index,             // uint32_t                               srcQueueFamilyIndex
			_graphicInstance->GetPresentQueue().index,             // uint32_t                               dstQueueFamilyIndex
			swapChainImages[i],                       // VkImage                                image
			image_subresource_range                     // VkImageSubresourceRange                subresourceRange
		};

		vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

		//
		//


		vkCmdPipelineBarrier(commandBuffers[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_present_to_clear);



		vkCmdClearColorImage(commandBuffers[i], swapChainImages[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clear_color, 1, &image_subresource_range);



		vkCmdPipelineBarrier(commandBuffers[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_clear_to_present);


		//
		//


		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}

void VulkanWrapper::VWBufferClear::CreateCommandPool(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	VWGraphicInstance::QueueFamilyIndices queueFamilyIndices = _graphicInstance->FindQueueFamilies(_graphicInstance->GetPhysicalDevice(), _graphicInstance->GetSurface());

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

	if (vkCreateCommandPool(_graphicInstance->GetDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}
