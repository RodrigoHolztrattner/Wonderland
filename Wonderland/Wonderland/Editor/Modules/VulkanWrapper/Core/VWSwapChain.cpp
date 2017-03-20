////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWSwapChain.h"
#include "VWGraphicAdapter.h"
#include "VWWindow.h"
#include "VWGraphicInstance.h"
#include "VWCoreUtils.h"

VulkanWrapper::VWSwapChain::VWSwapChain()
{
	// Set the initial data
	m_SwapChain = VK_NULL_HANDLE;
	m_ImageAvailableSemaphore = VK_NULL_HANDLE;
	m_RenderFinishedSemaphore = VK_NULL_HANDLE;
}

VulkanWrapper::VWSwapChain::~VWSwapChain()
{
}

bool VulkanWrapper::VWSwapChain::Initialize()
{
	return true;
}

VkFormat findSupportedFormat(VulkanWrapper::VWGraphicInstance* _graphicInstance, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(_graphicInstance->GetPhysicalDevice(), format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

VkFormat findDepthFormat(VulkanWrapper::VWGraphicInstance* _graphicInstance)
{
	return findSupportedFormat(_graphicInstance, 
	{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

void VulkanWrapper::VWSwapChain::CreateDepthResources(VulkanWrapper::VWGraphicInstance* _graphicInstance)
{
	VkFormat depthFormat = findDepthFormat(_graphicInstance);

	m_DepthImage.CreateImage(_graphicInstance, m_SwapChainExtent.width, m_SwapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	m_DepthImage.CreateImageView(_graphicInstance, VK_IMAGE_ASPECT_DEPTH_BIT);

	m_DepthImage.TransitionImageLayout(_graphicInstance, _graphicInstance->GetCommandPool(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

bool VulkanWrapper::VWSwapChain::CreateSwapChain(VWGraphicAdapter* _adapter, VWWindow* _window, VWGraphicInstance* _graphicInstance)
{
	SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_graphicInstance->GetPhysicalDevice(), _graphicInstance->GetSurface());

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, _window);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}
	
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = _graphicInstance->GetSurface();
	
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	VWGraphicInstance::QueueFamilyIndices indices = _graphicInstance->FindQueueFamilies(_graphicInstance->GetPhysicalDevice(), _graphicInstance->GetSurface());
	uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	VkSwapchainKHR oldSwapChain = m_SwapChain;
	createInfo.oldSwapchain = oldSwapChain;

	VkSwapchainKHR newSwapChain;
	if (vkCreateSwapchainKHR(_graphicInstance->GetDevice(), &createInfo, nullptr, &newSwapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	m_SwapChain = newSwapChain;

	vkGetSwapchainImagesKHR(_graphicInstance->GetDevice(), m_SwapChain, &imageCount, nullptr);
	m_SwapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(_graphicInstance->GetDevice(), m_SwapChain, &imageCount, m_SwapChainImages.data());

	m_SwapChainImageFormat = surfaceFormat.format;
	m_SwapChainExtent = extent;
}

bool VulkanWrapper::VWSwapChain::IsDeviceSuitable(VkPhysicalDevice _device, VWGraphicInstance* _graphicInstance, VkSurfaceKHR _surface)
{
	VWGraphicInstance::QueueFamilyIndices indices = _graphicInstance->FindQueueFamilies(_device, _surface);

	bool extensionsSupported = _graphicInstance->CheckDeviceExtensionSupport(_device);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_device, _surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

void VulkanWrapper::VWSwapChain::CreateImageViews(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	m_SwapChainImageViews.resize(m_SwapChainImages.size(), VkImageView());

	for (uint32_t i = 0; i < m_SwapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = m_SwapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_SwapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(_graphicInstance->GetDevice(), &createInfo, nullptr, &m_SwapChainImageViews[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}
}

void VulkanWrapper::VWSwapChain::CreateSemaphores(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(_graphicInstance->GetDevice(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore) != VK_SUCCESS || vkCreateSemaphore(_graphicInstance->GetDevice(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create semaphores!");
	}
}

void VulkanWrapper::VWSwapChain::CreateBackgroundCleaner(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	m_BackgroundCleaner.Initialize();
	m_BackgroundCleaner.CreateCommandPool(_adapter, _graphicInstance);
	m_BackgroundCleaner.CreateCommandBuffers(_adapter, _graphicInstance, this);
}

uint32_t VulkanWrapper::VWSwapChain::AcquireNextImage(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance)
{
	uint32_t imageIndex;
	vkAcquireNextImageKHR(_graphicInstance->GetDevice(), m_SwapChain, std::numeric_limits<uint64_t>::max(), m_ImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	return imageIndex;
}

void VulkanWrapper::VWSwapChain::SubmitGraphicQueue(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, const VkCommandBuffer* _commandBuffers, int _totalCommandBuffers, uint32_t _imageIndex)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	std::vector<VkCommandBuffer> commandBuffers;
	for (int i = 0; i < _totalCommandBuffers + 1; i++)
	{
		if (i == 0)
		{
			VkCommandBuffer temp = m_BackgroundCleaner.GetCommandBuffersReference()[_imageIndex];
			commandBuffers.push_back(temp);
		}
		else
		{
			commandBuffers.push_back(_commandBuffers[i-1]);
		}
	}

	submitInfo.commandBufferCount = commandBuffers.size();
	submitInfo.pCommandBuffers = commandBuffers.data();

	VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(_graphicInstance->GetGraphicQueue().queue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	//
	//
	//

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_SwapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &_imageIndex;

	vkQueuePresentKHR(_graphicInstance->GetPresentQueue().queue, &presentInfo);
}

void VulkanWrapper::VWSwapChain::PresentQueue(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, uint32_t _imageIndex)
{
	// Codigo repetido da parte acima!!!
	VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore };
	//


}

VulkanWrapper::VWSwapChain::SwapChainSupportDetails VulkanWrapper::VWSwapChain::QuerySwapChainSupport(VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, _surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, _surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}


VkSurfaceFormatKHR VulkanWrapper::VWSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR VulkanWrapper::VWSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanWrapper::VWSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VWWindow* _window)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		VkExtent2D actualExtent = { _window->GetWidth(), _window->GetHeight() };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}
