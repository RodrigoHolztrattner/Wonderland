////////////////////////////////////////////////////////////////////////////////
// Filename: VWGraphicAdapter.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\NamespaceDefinitions.h"

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
class VWGraphicInstance;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWGraphicAdapter
////////////////////////////////////////////////////////////////////////////////
class VWGraphicAdapter
{
public:

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
		std::cerr << "validation layer: " << msg << std::endl;
		return VK_FALSE;
	}

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWGraphicAdapter();
	~VWGraphicAdapter();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize();

	// Create the main vulkan instance
	bool CreateVulkanInstance(const char* _applicationName, const char* _engineName, uint32_t _applicationVersion, uint32_t _engineVersion);

	void SetupDebugCallback();

	// Return the instance adapter
	VkInstance GetInstanceAdapter(){return m_VulkanInstance;}

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

	// Our main vkinstance
	VkInstance m_VulkanInstance;

	VkDebugReportCallbackEXT callback;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)