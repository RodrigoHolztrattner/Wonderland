////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderCommandBase.h
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
#include "..\Renderable\VWRenderable.h"

#include "..\Resource\VWBuffer.h"

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

class VWContext;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWShaderCommandBase
////////////////////////////////////////////////////////////////////////////////
class VWShaderCommandBase
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderCommandBase();
	~VWShaderCommandBase();

////////////////////
// COMMAND BUFFER //
protected: /////////

	// Create a command buffer
	VkCommandBuffer CreateCommandBuffer(VWContext* _context, VkCommandBufferLevel _level, VkCommandPoolCreateFlags _flags);

	// Create multiple command buffers
	std::vector<VkCommandBuffer> CreateCommandBuffer(VWContext* _context, VkCommandBufferLevel _level, VkCommandPoolCreateFlags _flags, uint32_t _amount);

private:

	// Create the command pool
	void CreateCommandPool(VWContext* _context, VkCommandPoolCreateFlags _flags);

///////////////
// VARIABLES //
private: //////

	// If we use a custom command allocator
	bool m_UseCustomCommandPoolAllocator;

	// Our command pool
	VkCommandPool m_CommandPool;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)