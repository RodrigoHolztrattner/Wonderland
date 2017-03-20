////////////////////////////////////////////////////////////////////////////////
// Filename: VWGraphicInstance.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

#include "VWWindow.h"

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

class VWWindow;
class VWSwapChain;
class VWGraphicAdapter;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWGraphicInstance
////////////////////////////////////////////////////////////////////////////////
class VWGraphicInstance
{
public:

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete()
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	static std::vector<const char*> deviceExtensions;

	struct QueueHolder
	{
		// The queue itself and the index
		VkQueue queue;
		int index;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWGraphicInstance();
	~VWGraphicInstance();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize();

	// Create a vulkan surface using a glfw window
	void CreateSurface(VWGraphicAdapter* _adapter, VWWindow* _window);

	// Create a suitable physical device
	void CreateSuitablePhysicalDevice(VWGraphicAdapter* _adapter);

	// Create the logical device
	void CreateLogicalDevice(VulkanWrapper::VWGraphicAdapter* _adapter);

	// Create the command pool
	void CreateCommandPool(VulkanWrapper::VWGraphicAdapter* _adapter);

	//
	//
	//

	// Return the device
	VkDevice GetDevice() { return m_VulkanDevice; }

	// Return the surface
	VkSurfaceKHR GetSurface() { return m_Surface; }

	// Return the physical device
	VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
   
	// Return the graphic queue
	QueueHolder GetGraphicQueue() { return m_GraphicsQueue; }

	// Return the present queue
	QueueHolder GetPresentQueue() { return m_PresentQueue; }

	// Return the command pool
	VkCommandPool GetCommandPool() { return m_CommandPool; }

	//
	//
	//

	// Find the queue families for a given device
	static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR _surface);

	// Check the given device for supported extensions
	static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

private:

/////////////
// HELPERS //
public: /////

	// Check for validation support layer
	bool CheckValidationLayerSupport();

	// Get the required extensions
	std::vector<const char*> GetRequiredExtensions();

///////////////
// VARIABLES //
private: //////

	// Our main vulkan device
	VkDevice m_VulkanDevice;

	// The vulkan surface (multiple window)
	VkSurfaceKHR m_Surface;

	// The physical device we are using
	VkPhysicalDevice m_PhysicalDevice;

	QueueHolder m_GraphicsQueue;
	QueueHolder m_PresentQueue;

	// The command pool
	VkCommandPool m_CommandPool;

	// VkQueue m_GraphicsQueue;
	// VkQueue m_PresentQueue;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)