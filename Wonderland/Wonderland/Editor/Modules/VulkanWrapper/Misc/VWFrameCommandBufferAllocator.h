////////////////////////////////////////////////////////////////////////////////
// Filename: VWFrameCommandBufferAllocator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "..\..\NamespaceDefinitions.h"

#include <vector>

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
class VWGraphicAdapter;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWFrameCommandBufferAllocator
////////////////////////////////////////////////////////////////////////////////
class VWFrameCommandBufferAllocator
{
public:

	struct CommandPoolAux
	{
		VkCommandPool sCommandPool;
		uint32_t sTargetCommandBuffer;
		std::vector<VkCommandBuffer> sValidCommandBuffers;
	};

	// The per thread data
	struct CommandDataPerThread
	{
		// uint32_t targetCommandBuffer;
		// std::vector<VkCommandBuffer> validCommandBuffers;
		std::vector<CommandPoolAux> sCommandPoolAux;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWFrameCommandBufferAllocator();
	~VWFrameCommandBufferAllocator();

//////////////////
// MAIN METHODS //
public: //////////

	// Initialize
	bool Initialize(VWGraphicAdapter* _adapter, VWGraphicInstance* _graphicInstance, uint32_t _totalThreads, uint32_t _bufferingMagnitude);

	// Create a command buffer valid for the current frame
	VkCommandBuffer CreateFrameCommandBuffer(VWGraphicInstance* _graphicInstance, VkCommandBufferLevel _level, uint32_t _threadIndex);

	// Clean the current frame command data
	void ResetCommandBuffers(VWGraphicInstance* _graphicInstance);

///////////////
// VARIABLES //
private: //////

	// All command pools
	std::vector<CommandDataPerThread> m_ThreadCommandData;

	// The total of frames and the current frame
	uint32_t m_TotalFrameMagnitude;
	uint32_t m_CurrentFrameMagnitude;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)