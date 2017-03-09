////////////////////////////////////////////////////////////////////////////////
// Filename: VWSwapChain.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>

#include "VWBufferClear.h"

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

////////////////
// FORWARDING //
////////////////

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

class VWGraphicAdapter;
class VWWindow;
class VWGraphicInstance;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWSwapChain
////////////////////////////////////////////////////////////////////////////////
class VWSwapChain
{
public:

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWSwapChain();
	~VWSwapChain();

	// Check if a given device is suitable
	static bool IsDeviceSuitable(VkPhysicalDevice _device, VWGraphicInstance* _graphicInstance, VkSurfaceKHR _surface);

	// Query the swap chain supporte details for a given device
	static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface);

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize the swap chain object
	bool Initialize();

	// Create the swap chain
	bool CreateSwapChain(VulkanWrapper::VWGraphicAdapter* _adapter, VWWindow* _window, VWGraphicInstance* _graphicInstance);

	void CreateImageViews(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	void CreateSemaphores(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	// Create our background cleaner
	void CreateBackgroundCleaner(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);
	

	uint32_t AcquireNextImage(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

	void SubmitGraphicQueue(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, const VkCommandBuffer* _commandBuffers, int _totalCommandBuffers, uint32_t _imageIndex);

	void PresentQueue(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, uint32_t _imageIndex);

	// Return the swap chain
	VkSwapchainKHR GetSwapChain() { return m_SwapChain; }

	// Return the swap chain format
	VkFormat GetFormat() { return m_SwapChainImageFormat; }

	// Return the swap chain extent
	VkExtent2D GetExtent() { return m_SwapChainExtent; }

	// Return the swap chain images
	const std::vector<VkImage>& GetImages() { return m_SwapChainImages; }

	// Return the swap chain image views
	const std::vector<VkImageView>& GetImageViews() { return m_SwapChainImageViews; }

	//

	// Return the image avaliable semaphore
	VkSemaphore GetImageAvaliableSemaphore() { return m_ImageAvailableSemaphore; }

	// Return the render finished semaphore
	VkSemaphore GetRenderFinishedSemaphore() { return m_RenderFinishedSemaphore; }


private:

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VWWindow* _window);

///////////////
// VARIABLES //
private: //////

	// Our swap chain
	VkSwapchainKHR m_SwapChain;

	// The swap chain images and the format
	std::vector<VkImage> m_SwapChainImages;
	VkFormat m_SwapChainImageFormat;

	// The swap chain extent
	VkExtent2D m_SwapChainExtent;

	std::vector<VkImageView> m_SwapChainImageViews;

	VkSemaphore m_ImageAvailableSemaphore;
	VkSemaphore m_RenderFinishedSemaphore;

	// Our buffer cleaner
	VWBufferClear m_BackgroundCleaner;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)