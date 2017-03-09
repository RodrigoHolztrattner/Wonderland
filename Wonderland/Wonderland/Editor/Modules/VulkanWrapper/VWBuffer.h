////////////////////////////////////////////////////////////////////////////////
// Filename: VWBuffer.h
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
#include <array>
#include <glm/glm.hpp>

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

class VWContext;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: VWBuffer
////////////////////////////////////////////////////////////////////////////////
class VWBuffer
{
public:


//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWBuffer();
	~VWBuffer();

//////////////////
// MAIN METHODS //
public: //////////

	// Create this buffer
	void Create(VWContext* _context, VkBufferUsageFlags _usage, const void* _data, VkDeviceSize _size);

	// Create this buffer using extended configuration
	void CreateEx(VWContext* _context, VkBufferUsageFlags _normalUsage, VkBufferUsageFlags _staggingUsage, VkMemoryPropertyFlags _normalProperties, VkMemoryPropertyFlags _staggingProperties, const void* _data, VkDeviceSize _size);

	// Update the buffer with the given data
	void Update(VWContext* _context, const void* _data);

	// Release this buffer
	void Release();

	// Return if this buffer was initialized
	bool IsRead();

public:

	// Return the size
	VkDeviceSize GetSize() { return m_BufferSize; }

	// Return the buffer
	VkBuffer GetRawBuffer() { return m_Buffer; }

	// Return the stagging buffer
	VkBuffer GetRawStaggingBuffer() { return m_StagingBuffer; }

private:

	// Create a buffer
	void CreateBuffer(VWContext* _context, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	// Copy a buffer
	void CopyBuffer(VWContext* _context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

///////////////
// VARIABLES //
private: //////

	// If this buffer was initialized
	bool m_Initialized;

	// Our buffer and memory
	VkBuffer m_Buffer;
	VkDeviceMemory m_BufferMemory;

	// Our stagging buffer and memory
	VkBuffer m_StagingBuffer;
	VkDeviceMemory m_StagingBufferMemory;

	// The buffer size
	VkDeviceSize m_BufferSize;

	// VkCommandBuffer commandBuffer;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)