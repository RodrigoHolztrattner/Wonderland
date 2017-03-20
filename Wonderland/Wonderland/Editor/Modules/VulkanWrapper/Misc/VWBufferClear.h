////////////////////////////////////////////////////////////////////////////////
// Filename: VWBufferClear.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <glm/glm.hpp>

#include "..\Core\VWGraphicAdapter.h"

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

class VWGraphicAdapter;
class VWWindow;
class VWSwapChain;
class VWGraphicInstance;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWBufferClear
////////////////////////////////////////////////////////////////////////////////
class VWBufferClear
{
public:


//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWBufferClear();
	~VWBufferClear();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize this render shard object
	bool Initialize();

	// Return a reference to all command buffers
	const std::vector<VkCommandBuffer>& GetCommandBuffersReference() { return commandBuffers; }

	void CreateCommandBuffers(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, VWSwapChain* _swapChain);

	void CreateCommandPool(VulkanWrapper::VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance);

///////////////
// VARIABLES //
private: //////

	VkCommandPool commandPool;

	std::vector<VkCommandBuffer> commandBuffers;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)